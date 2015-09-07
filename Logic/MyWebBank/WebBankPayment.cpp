#include "WebBankPayment.h"
#include "WebBankDataBaseManip.h"
#include "WebBankCurrentUser.h"
#include <QTime>

//默认构造函数
WPayment::WPayment(){}

//带参数的默认构造函数
WPayment::WPayment(QString accountNumber, float sum, QString paymentType){
    number = accountNumber;
    sum = sum;
    type = paymentType;
    haveAutoPayment[1] = haveAutoPayment[2] = haveAutoPayment[3] = false;
    DBAccountManip dbAccount;
    QVector<QString> accountInfo = dbAccount.dbSelect(number);
    currentDeposit = (accountInfo[4].toFloat());
    fixedDeposit = accountInfo[3].toFloat();
    QString selectInfo = QString("SELECT * FROM autoPay WHERE accountKey = %1").arg(DBAccountManip::dbSelectAccountKey(number));
    DBAutoPayManip dbAutoPay;
    QVector<QString> autoPayInfo;
    autoPayInfo = dbAutoPay.dbSelect(selectInfo);
    int size = autoPayInfo.size()/3;
    for(int i = 0;i<size;i++){
        haveAutoPayment[i] = true;
        autoPayDate = autoPayInfo[2 + 3*i];
        autoPayType = autoPayInfo[1 + 3*i];
    }
}

//设置对象的私有变量中haveAutoPayment和autoPayDate
void WPayment::setAutoPayment(bool ifChoose[]){
    for(int i = 0;i<3;i++)
        haveAutoPayment[i] = ifChoose[i];
    for(int i = 0;i<3;i++){
        if(haveAutoPayment[i]){
            autoPayDate[i] = QDate::currentDate();
        }
    }
}

//查询是否有自动付款项目
bool WPayment::isAutoPaymentEmpty(){
    for(int i = 0;i<3;i++){
        if(haveAutoPayment[i] == true)
            return false;//有自动缴费项目
    }
    return true;//无自动缴费项目
}

//付款
bool WPayment::pay(){
    if(currentDeposit<sum)//钱不够
        return false;
    else{
        //更改账户中的存款余额
        currentDeposit -= sum;
        DBAccountManip dbAccount;
        bool result = dbAccount.dbPaymentUpdate(number,currentDeposit);
        //在payment表中插入一条新信息
        QVector<QString> insertInfo;
        int key = DBAccountManip::dbSelectAccountKey(number);
        QString accountKey = QString::setNum(key);
        insertInfo.push_back(accountKey);
        QString Sum = QString::setNum(sum);
        insertInfo.push_back(Sum);
        QString CurrentDeposit = QString::setNum(currentDeposit);
        insertInfo.push_back(CurrentDeposit);
        insertInfo.push_back(type);
        if(result){
            DBPaymetnRecordManip paymentManip;
            result = paymentManip.dbInsert(insertInfo);
        }
        return result;
    }
}

//自动付款，（暂时未测试）
bool WPayment::autoPayment(){
    bool result[3] = {true,true,true};
    DBMessageManip messageManip;
    for(int i = 0;i<3;i++){
        if(haveAutoPayment[i]){
            if(QDate::currentDate()>= autoPayDate[i].addMonths(1)){
                type = Type;
                int months = 0;
                bool r;
                while(QDate::currentDate()>=autoPayDate[i].addMonths(1)){
                    months++;
                    autoPayDate[i] = autoPayDate[i].addMonths(1);
                    qsrand(time(NULL));
                    sum = (100 + qrand()%50);
                    type = autoPayType[i];
                    r = pay();
                    QVector<QString> insertInfo;
                    QString userKey = QString("%1").arg(DBUserManip::dbSelectUserKey(WCurrentUser::userName));
                    insertInfo.push_back(userKey);
                    insertInfo.push_back(autoPayDate[i].toString());
                    insertInfo.push_back(QString("auto pay for the %1").arg(autoPayType[i]));
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

//删除自动付款的项目
bool WPayment::deleteAutoPayment(QString paymentType[]){
    bool result[3] = {true,true,true};
    for(int i = 0;i<3;i++)
        for(int j = 0;j<3;j++){
            if(autoPayType[j] == paymentType[i]){
                DBAutoPayManip autoPayManip;
                result[i] = autoPayManip.dbDelete(number,autoPayType[i]);
                autoPayType[i] = "";
                if(!result[i])
                    return false;
            }
        }
    return true;
}
