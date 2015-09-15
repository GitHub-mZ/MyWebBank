#include "wpayment.h"
#include "wDBmanip.h"
#include "wcurrentuser.h"
#include <QTime>

WPayment::WPayment() {}

WPayment::WPayment(QString accountNumber, float sum, QString paymentType)
{
    number = accountNumber;
    this->sum = sum;
    type = paymentType;
    haveAutoPayment[1] = haveAutoPayment[2] = haveAutoPayment[3] = false;
    DBAccountManip dbAccount;
    QVector<QString> accountInfo = dbAccount.dbSelect(number);
    currentDeposit = (accountInfo[3].toFloat());
    fixedDeposit = accountInfo[2].toFloat();
    QString selectInfo = QString("SELECT * FROM autoPay WHERE accountKey = %1").arg(DBAccountManip::dbSelectAccountKey(number));
    DBAutoPayManip dbAutoPay;
    QVector<QString> autoPayInfo;
    autoPayInfo = dbAutoPay.dbSelect(selectInfo);
    int size = autoPayInfo.size() / 3;
    for(int i = 0; i < size; i++)
    {
        haveAutoPayment[i] = true;
        QDateTime time = QDateTime::fromString(autoPayInfo[2 + 3 * i]);
        autoPayDate[i] = time.date();
        autoPayType[i] = autoPayInfo[1 + 3 * i];
    }
}

void WPayment::setAutoPayment(bool ifChoose[])
{
    for(int i = 0; i < 3; i++)
        haveAutoPayment[i] = ifChoose[i];
    for(int i = 0; i < 3; i++)
    {
        if(haveAutoPayment[i])
        {
            autoPayDate[i] = QDate::currentDate();
        }
    }
}

bool WPayment::isAutoPaymentEmpty()
{
    for(int i = 0; i < 3; i++)
    {
        if(haveAutoPayment[i] == true)
            return false;
    }
    return true;
}

bool WPayment::pay()
{
    DBAccountManip dbAccount;
    QVector<QString> info = dbAccount.dbSelect(number);
    QString accountType = info[0];
    if((currentDeposit < sum && accountType == "normalAccount")
            || (currentDeposit + fixedDeposit < sum && accountType == "creditCard"))
        return false;
    else
    {
        currentDeposit -= sum;
        DBAccountManip dbAccount;
        bool result = dbAccount.dbPaymentUpdate(number, currentDeposit);

        QVector<QString> insertInfo;
        insertInfo.push_back(number);
        QString Sum;
        Sum.setNum(sum);
        insertInfo.push_back(Sum);
        insertInfo.push_back(type);
        QString CurrentDeposit;
        CurrentDeposit.setNum(currentDeposit);
        insertInfo.push_back(CurrentDeposit);
        if(result)
        {
            DBPaymentRecordManip paymentManip;
            result = paymentManip.dbInsert(insertInfo);
        }
        return result;
    }
}

bool WPayment::pay(int months)
{
    pay();
    QString str = QString("datetime('now','-%1 month')").arg(months);
    int key = DBPaymentRecordManip::dbSelectMaxKey();
    QString updateInfo = QString("UPDATE paymentRecord SET time = %1 WHERE key = %2").arg(str).arg(key);
    DBPaymentRecordManip paymentManip;
    bool result = paymentManip.dbUpdate(updateInfo);
    return result;
}

bool WPayment::autoPayment()
{
    bool result[3] = {true,true,true};
    DBMessageManip messageManip;
    for(int i = 0;i<3;i++){
        if(haveAutoPayment[i]){
            if(QDate::currentDate()>= autoPayDate[i].addMonths(1)){
                type = autoPayType[i];
                int months = 0;
                bool r;
                while(QDate::currentDate()>=autoPayDate[i].addMonths(months))
                    months++;
                months--;
                for(int j = 0;j<months;j++){
                    autoPayDate[i] = autoPayDate[i].addMonths(1);
                    QTime time = QTime::currentTime();
                    qsrand(time.msec()+time.second()*1000);
                    sum = (100 + qrand()%50);
                    type = autoPayType[i];
                    r = pay(months - j);
                    QVector<QString> insertInfo;
                    QString userKey = QString("%1").arg(DBUserManip::dbSelectUserKey());
                    insertInfo.push_back(userKey);
                    QString str;
                    str.setNum(months - j);
                    insertInfo.push_back(str);
                    insertInfo.push_back(QString("auto pay %1 for the %2").arg(sum).arg(autoPayType[i]));
                    messageManip.dbInsert(insertInfo);
                }
                result[i] = r;
            }
        }
    }
    for(int i = 0;i<3;i++)
        if(!result[i])
            return false;
    return true;
}

bool WPayment::deleteAutoPayment(QString paymentType[])
{
    bool result[3] = {true, true, true};
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            if(autoPayType[j] == paymentType[i])
            {
                DBAutoPayManip autoPayManip;
                result[i] = autoPayManip.dbDelete(number, autoPayType[i]);
                autoPayType[i] = "";
                if(!result[i])
                    return false;
            }
        }
    return true;
}
