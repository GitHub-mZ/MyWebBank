#include "wdelegate.h"
#include "pages.h"
#include <QHeaderView>
#include <QListWidget>

WPage::WPage(QWidget *parent): QWidget(parent)
{
    mainTitle = new QLabel(this);
    mainTitle->setObjectName("Title");
}

MyAccountPage::MyAccountPage(QWidget *parent) : WPage(parent)
{
    bgLabel = new QLabel(this);
    mainTitle->setText(tr("My Account"));
    title2 = new QLabel(tr("Recent Transaction Records"), this);
    table1 = new QTableWidget(this);
    table2 = new QTableWidget(this);

    bgLabel->setObjectName("CMAbg");
    title2->setObjectName("CMALabel2");
    table1->setObjectName("CMATable1");
    table2->setObjectName("CMATable2");

    bgLabel->setGeometry(QRect(0, 0, 751, 566));
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    title2->setGeometry(QRect(24, 280, 708, 48));
    table1->setGeometry(QRect(24, 72, 708, 192));
    table2->setGeometry(QRect(24, 336, 708, 192));

    table1->setColumnCount(3);
    table1->setRowCount(5);
    table2->setColumnCount(3);
    table2->setRowCount(5);

    QStringList headers;
    headers << "ID" << "Name" << "Age" << "Sex";
    table1->setHorizontalHeaderLabels(headers);
    table2->setHorizontalHeaderLabels(headers);

    table1->setItem(0, 0, new QTableWidgetItem(QString("0001")));
    table1->setItem(1, 0, new QTableWidgetItem(QString("0002")));
    table1->setItem(2, 0, new QTableWidgetItem(QString("0003")));
    table1->setItem(3, 0, new QTableWidgetItem(QString("0004")));
    table1->setItem(4, 0, new QTableWidgetItem(QString("0005")));
    table1->setItem(5, 0, new QTableWidgetItem(QString("0006")));
    table1->setItem(0, 1, new QTableWidgetItem(QString("20100112")));

    table2->setItem(0, 0, new QTableWidgetItem(QString("0001")));
    table2->setItem(1, 0, new QTableWidgetItem(QString("0002")));
    table2->setItem(2, 0, new QTableWidgetItem(QString("0003")));
    table2->setItem(3, 0, new QTableWidgetItem(QString("0004")));
    table2->setItem(4, 0, new QTableWidgetItem(QString("0005")));
    table2->setItem(5, 0, new QTableWidgetItem(QString("0006")));
    table2->setItem(0, 1, new QTableWidgetItem(QString("20100112")));

    WDelegate *CMADele1 = new WDelegate();
    table1->setItemDelegate(CMADele1);

    table1->verticalHeader()->hide();
    table1->horizontalHeader()->setStretchLastSection(true);
    table1->setShowGrid(false);
    table1->setSelectionBehavior(QAbstractItemView::SelectRows);
    table1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table1->horizontalHeader()->resizeSection(0, 150);
    table1->verticalHeader()->setDefaultSectionSize(48);

    table2->verticalHeader()->hide();
    table2->horizontalHeader()->setStretchLastSection(true);
    table2->setShowGrid(false);
    table2->setSelectionBehavior(QAbstractItemView::SelectRows);
    table2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table2->horizontalHeader()->resizeSection(0, 150);
    table2->verticalHeader()->setDefaultSectionSize(48);
}

void MyAccountPage::updateLanguage()
{
    mainTitle->setText(tr("My Account"));
    title2->setText(tr("Recent Transaction Records"));
}

AccountQueryPage::AccountQueryPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("Account Query"));

    label1 = new QLabel(tr("Account"), this);
    label2 = new QLabel(tr("Date range"), this);
    accountBox = new QComboBox(this);
    incomeCkBox = new QCheckBox(tr("Income"), this);
    expenseCkBox = new QCheckBox(tr("Expense"), this);
    searchBtn = new QPushButton(tr("SEARCH"), this);
    recentBtn = new QPushButton(tr("Recent Three Months"), this);
    fromDate = new QLineEdit(this);
    toDate = new QLineEdit(this);
    table = new QTableWidget(this);

    label1->setObjectName("CAQLabel");
    label2->setObjectName("CAQDate");
    accountBox->setObjectName("CAQAccount");
    incomeCkBox->setObjectName("CAQIncome");
    expenseCkBox->setObjectName("CAQExpense");
    searchBtn->setObjectName("CAQSearch");
    recentBtn->setObjectName("CAQRecent");
    fromDate->setObjectName("CAQFrom");
    toDate->setObjectName("CAQTo");
    table->setObjectName("CAQTable");

    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(368, 92, 100, 24));
    accountBox->setGeometry(QRect(124, 92, 200, 24));
    incomeCkBox->setGeometry(QRect(24, 140, 100, 24));
    expenseCkBox->setGeometry(QRect(154, 140, 100, 24));
    searchBtn->setGeometry(QRect(624, 134, 108, 36));
    recentBtn->setGeometry(QRect(368, 134, 230, 36));
    fromDate->setGeometry(QRect(490, 92, 108, 24));
    toDate->setGeometry(QRect(628, 92, 108, 24));
    table->setGeometry(QRect(24, 192, 708, 336));

    accountBox->addItem("1231 2312 3123 1236");
    accountBox->addItem("2175 7962 4595 4698");
    WDelegate *CMADele = new WDelegate();
    accountBox->setItemDelegate(CMADele);

    table->setColumnCount(3);
    table->setRowCount(5);

    QStringList headers;
    headers << "ID" << "Name" << "Age" << "Sex";
    table->setHorizontalHeaderLabels(headers);
    table->setItem(0, 0, new QTableWidgetItem(QString("0001")));
    table->setItem(1, 0, new QTableWidgetItem(QString("0002")));
    table->setItem(2, 0, new QTableWidgetItem(QString("0003")));
    table->setItem(3, 0, new QTableWidgetItem(QString("0004")));
    table->setItem(4, 0, new QTableWidgetItem(QString("0005")));
    table->setItem(5, 0, new QTableWidgetItem(QString("0006")));
    table->setItem(0, 1, new QTableWidgetItem(QString("20100112")));
    WDelegate *CAQDele = new WDelegate();
    table->setItemDelegate(CAQDele);
    table->verticalHeader()->hide();
    table->horizontalHeader()->setStretchLastSection(true);
    table->setShowGrid(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->resizeSection(0, 150);
    table->verticalHeader()->setDefaultSectionSize(48);

    fromDate->setPlaceholderText("YYYY.MM.DD");
    toDate->setPlaceholderText("YYYY.MM.DD");
    QRegExp dateRestriction("[1-2][0-9]{3}\\.[0-9]{1,2}\\.[0-9]{1,2}");
    toDate->setValidator(new QRegExpValidator(dateRestriction, this));
    fromDate->setValidator(new QRegExpValidator(dateRestriction, this));
}

void AccountQueryPage::updateLanguage()
{
    mainTitle->setText(tr("Account Query"));
    label1->setText(tr("Account"));
    label2->setText(tr("Date Range"));
    incomeCkBox->setText(tr("Income"));
    expenseCkBox->setText(tr("Expense"));
    searchBtn->setText(tr("SEARCH"));
    recentBtn->setText(tr("Recent Three Months"));
}

TransferPage::TransferPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("Current Deposit Transfer"));
    label1 = new QLabel(tr("Paying account"), this);
    label2 = new QLabel(tr("Receiver's name"), this);
    label3 = new QLabel(tr("Receiver's account"), this);
    label4 = new QLabel(tr("Transfer amount"), this);
    label5 = new QLabel(tr("Comment"), this);
    edit1 = new QComboBox(this);
    edit2 = new QLineEdit(this);
    edit3 = new QLineEdit(this);
    edit4 = new QLineEdit(this);
    edit5 = new QLineEdit(this);
    confirmBtn = new QPushButton(tr("CONFIRM"), this);

    label1->setObjectName("CTLabel1");
    label2->setObjectName("CTLabel2");
    label3->setObjectName("CTLabel3");
    label4->setObjectName("CTLabel4");
    label5->setObjectName("CTLabel5");
    edit1->setObjectName("CTEdit1");
    edit2->setObjectName("CTEdit2");
    edit3->setObjectName("CTEdit3");
    edit4->setObjectName("CTEdit4");
    edit5->setObjectName("CTEdit5");
    confirmBtn->setObjectName("CTConfirmBtn");

    edit1->addItem("1231 2312 3123 1236");
    edit1->addItem("2175 7962 4595 4698");
    WDelegate *CTDele = new WDelegate();
    edit1->setItemDelegate(CTDele);

    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(24, 140, 200, 24));
    label3->setGeometry(QRect(24, 188, 200, 24));
    label4->setGeometry(QRect(24, 236, 200, 24));
    label5->setGeometry(QRect(24, 284, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    edit2->setGeometry(QRect(288, 136, 400, 32));
    edit3->setGeometry(QRect(288, 184, 400, 32));
    edit4->setGeometry(QRect(288, 232, 400, 32));
    edit5->setGeometry(QRect(288, 280, 400, 32));
    confirmBtn->setGeometry(QRect(584, 336, 108, 36));
}

void TransferPage::updateLanguage()
{
    mainTitle->setText(tr("Current Deposit Transfer"));
    label1->setText(tr("Paying account"));
    label2->setText(tr("Receiver's name"));
    label3->setText(tr("Receiver's account"));
    label4->setText(tr("Transfer amount"));
    label5->setText(tr("Comment"));
    confirmBtn->setText(tr("CONFIRM"));
}

CurrentFixPage::CurrentFixPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("Current Fixed Transfer"));
    label1 = new QLabel(tr("Paying account"), this);
    label2 = new QLabel(tr("Receiver's name"), this);
    label3 = new QLabel(tr("Receiver's account"), this);
    label4 = new QLabel(tr("Transfer type"), this);
    label5 = new QLabel(tr("Transfer amount"), this);
    edit1 = new QComboBox(this);
    edit2 = new QLineEdit(this);
    edit3 = new QLineEdit(this);
    edit4 = new QComboBox(this);
    edit5 = new QLineEdit(this);
    confirmBtn = new QPushButton(tr("CONFIRM"), this);

    label1->setObjectName("CCFLabel1");
    label2->setObjectName("CCFLabel2");
    label3->setObjectName("CCFLabel3");
    label4->setObjectName("CCFLabel4");
    label5->setObjectName("CCFLabel5");
    edit1->setObjectName("CCFEdit1");
    edit2->setObjectName("CCFEdit2");
    edit3->setObjectName("CCFEdit3");
    edit4->setObjectName("CCFEdit4");
    edit5->setObjectName("CCFEdit5");
    confirmBtn->setObjectName("CCFConfirmBtn");


    edit1->addItem("1231 2312 3123 1236");
    edit1->addItem("2175 7962 4595 4698");
    WDelegate *CCFDele1 = new WDelegate();
    edit1->setItemDelegate(CCFDele1);

    edit4->addItem(tr("Current to Fix"));
    edit4->addItem(tr("Fix to Current"));
    WDelegate *CCFDele2 = new WDelegate();
    edit4->setItemDelegate(CCFDele2);

    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(24, 140, 200, 24));
    label3->setGeometry(QRect(24, 188, 200, 24));
    label4->setGeometry(QRect(24, 236, 200, 24));
    label5->setGeometry(QRect(24, 284, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    edit2->setGeometry(QRect(288, 136, 400, 32));
    edit3->setGeometry(QRect(288, 184, 400, 32));
    edit4->setGeometry(QRect(288, 232, 400, 32));
    edit5->setGeometry(QRect(288, 280, 400, 32));
    confirmBtn->setGeometry(QRect(584, 336, 108, 36));
}

void CurrentFixPage::updateLanguage()
{
    mainTitle->setText(tr("Current Fixed Transfer"));
    label1->setText(tr("Paying account"));
    label2->setText(tr("Receiver's name"));
    label3->setText(tr("Receiver's account"));
    label4->setText(tr("Transfer type"));
    label5->setText(tr("Transfer amount"));
    confirmBtn->setText(tr("CONFIRM"));
    edit4->clear();
    edit4->addItem(tr("Current to Fix"));
    edit4->addItem(tr("Fix to Current"));
    WDelegate *CCFDele2 = new WDelegate();
    edit4->setItemDelegate(CCFDele2);
}

PaymentPage::PaymentPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("Payment"));
    label1 = new QLabel(tr("Item"), this);
    label2 = new QLabel(tr("Paying account"), this);
    label3 = new QLabel(tr("Bill number"), this);
    edit1 = new QComboBox(this);
    edit2 = new QComboBox(this);
    edit3 = new QLineEdit(this);
    autoBtn = new QPushButton(tr("SET AUTOPAY"), this);
    confirmBtn = new QPushButton(tr("CONFIRM"), this);

    label1->setObjectName("CPLabel1");
    label2->setObjectName("CPLabel2");
    label3->setObjectName("CPLabel3");
    edit1->setObjectName("CPEdit1");
    edit2->setObjectName("CPEdit2");
    edit3->setObjectName("CPEdit3");
    autoBtn->setObjectName("CPAutoBtn");
    confirmBtn->setObjectName("CPConfirmBtn");

    edit1->addItem(tr("Water Bill"));
    edit1->addItem(tr("Electricity Bill"));
    edit1->addItem(tr("Gas Bill"));
    WDelegate *CPDele1 = new WDelegate();
    edit1->setItemDelegate(CPDele1);

    edit2->addItem("2175 7962 4595 4698");
    edit2->addItem("1745 7962 4595 4698");
    WDelegate *CPDele2 = new WDelegate();
    edit2->setItemDelegate(CPDele2);

    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(24, 140, 200, 24));
    label3->setGeometry(QRect(24, 188, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    edit2->setGeometry(QRect(288, 136, 400, 32));
    edit3->setGeometry(QRect(288, 184, 400, 32));
    autoBtn->setGeometry(QRect(430, 240, 148, 36));
    confirmBtn->setGeometry(QRect(584, 240, 108, 36));

    connect(autoBtn, SIGNAL(clicked(bool)), parent->parent(), \
            SLOT(showAutoPayPage()));
}

void PaymentPage::updateLanguage()
{
    mainTitle->setText(tr("Current Fixed Transfer"));
    label1->setText(tr("Paying account"));
    label2->setText(tr("Receiver's name"));
    label3->setText(tr("Receiver's account"));
    autoBtn->setText(tr("SET AUTOPAY"));
    confirmBtn->setText(tr("CONFIRM"));
    edit1->clear();
    edit1->addItem(tr("Water Bill"));
    edit1->addItem(tr("Electricity Bill"));
    edit1->addItem(tr("Gas Bill"));
    WDelegate *CPDele1 = new WDelegate();
    edit1->setItemDelegate(CPDele1);
}

AutoPayPage::AutoPayPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("Auto Payment"));
    label1 = new QLabel(tr("Item"), this);
    label2 = new QLabel(tr("Paying account"), this);
    title2 = new QLabel(tr("Already Set Auto Payments"), this);
    edit1 = new QComboBox(this);
    edit2 = new QComboBox(this);
    settingBtn = new QPushButton(tr("SET"), this);
    cancelBtn = new QPushButton(tr("CANCEL"), this);
    table = new QTableWidget(this);

    label1->setObjectName("CAPLabel1");
    label2->setObjectName("CAPLabel2");
    title2->setObjectName("CAPLabel3");
    edit1->setObjectName("CAPEdit1");
    edit2->setObjectName("CAPEdit2");
    settingBtn->setObjectName("CAPSettingBtn");
    cancelBtn->setObjectName("CAPCancelBtn");
    table->setObjectName("CAPTable");

    edit1->addItem(tr("Water Bill"));
    edit1->addItem(tr("Electricity Bill"));
    edit1->addItem(tr("Gas Bill"));
    WDelegate *CAPDele1 = new WDelegate();
    edit1->setItemDelegate(CAPDele1);

    edit2->addItem("2175 7962 4595 4698");
    edit2->addItem("1745 7962 4595 4698");
    WDelegate *CAPDele2 = new WDelegate();
    edit2->setItemDelegate(CAPDele2);

    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(24, 140, 200, 24));
    title2->setGeometry(QRect(24, 232, 708, 48));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    edit2->setGeometry(QRect(288, 136, 400, 32));
    settingBtn->setGeometry(QRect(596, 192, 96, 36));
    cancelBtn->setGeometry(QRect(484, 192, 96, 36));
    table->setGeometry(QRect(24, 288, 708, 240));

    table->setColumnCount(3);
    table->setRowCount(5);

    QStringList headers;
    headers << "ID" << "Name" << "Age" << "Sex";
    table->setHorizontalHeaderLabels(headers);
    table->setItem(0, 0, new QTableWidgetItem(QString("0001")));
    table->setItem(1, 0, new QTableWidgetItem(QString("0002")));
    table->setItem(2, 0, new QTableWidgetItem(QString("0003")));
    table->setItem(3, 0, new QTableWidgetItem(QString("0004")));
    table->setItem(4, 0, new QTableWidgetItem(QString("0005")));
    table->setItem(5, 0, new QTableWidgetItem(QString("0006")));
    table->setItem(0, 1, new QTableWidgetItem(QString("20100112")));
    WDelegate *CAPDele = new WDelegate();
    table->setItemDelegate(CAPDele);
    table->verticalHeader()->hide();
    table->horizontalHeader()->setStretchLastSection(true);
    table->setShowGrid(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->resizeSection(0, 150);
    table->verticalHeader()->setDefaultSectionSize(48);

}

void AutoPayPage::updateLanguage()
{
    mainTitle->setText(tr("Auto Payment"));
    label1->setText(tr("Item"));
    label2->setText(tr("Paying account"));
    title2->setText(tr("Already Set Auto Payments"));
    settingBtn->setText(tr("SET"));
    cancelBtn->setText(tr("CANCEL"));
    edit1->clear();
    edit1->addItem(tr("Water Bill"));
    edit1->addItem(tr("Electricity Bill"));
    edit1->addItem(tr("Gas Bill"));
    WDelegate *CAPDele1 = new WDelegate();
    edit1->setItemDelegate(CAPDele1);
}

CardApplyPage::CardApplyPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("Credit Card Apply"));
    label1 = new QLabel(tr("Card type"), this);
    edit1 = new QComboBox(this);
    confirmBtn = new QPushButton(tr("CONFIRM"), this);

    label1->setObjectName("CCALabel1");
    edit1->setObjectName("CCAEdit1");
    confirmBtn->setObjectName("CCAConfirmBtn");

    edit1->addItem(tr("TYPE 1"));
    edit1->addItem(tr("TYPE 2"));
    WDelegate *CCADele = new WDelegate();
    edit1->setItemDelegate(CCADele);

    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    confirmBtn->setGeometry(QRect(584, 144, 108, 36));
}

void CardApplyPage::updateLanguage()
{
    mainTitle->setText(tr("Credit Card Apply"));
    label1->setText(tr("Card type"));
    confirmBtn->setText(tr("CONFIRM"));
    edit1->clear();
    edit1->addItem(tr("TYPE 1"));
    edit1->addItem(tr("TYPE 2"));
    WDelegate *CCADele = new WDelegate();
    edit1->setItemDelegate(CCADele);
}

CardActivatePage::CardActivatePage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("Credit Card Activate"));
    label1 = new QLabel(tr("Card number"), this);
    edit1 = new QComboBox(this);
    activateBtn = new QPushButton(tr("ACTIVATE"), this);

    label1->setObjectName("CCBLabel1");
    edit1->setObjectName("CCBEdit1");
    activateBtn->setObjectName("CCBActivateBtn");

    edit1->addItem("1231 2312 3123 1236");
    edit1->addItem("2175 7962 4595 4698");
    WDelegate *CCBDele = new WDelegate();
    edit1->setItemDelegate(CCBDele);

    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    activateBtn->setGeometry(QRect(584, 144, 108, 36));
}

void CardActivatePage::updateLanguage()
{
    mainTitle->setText(tr("Credit Card Activate"));
    label1->setText(tr("Card number"));
    activateBtn->setText(tr("ACTIVATE"));
}

CardRepayPage::CardRepayPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("Credit Card Repay"));
    label1 = new QLabel(tr("Card number"), this);
    label2 = new QLabel(tr("Total repay amount"), this);
    label3 = new QLabel(tr("Minimum repay amount"), this);
    label4 = new QLabel(tr("Repay account"), this);
    label5 = new QLabel(tr("Repay ammount"), this);
    edit1 = new QComboBox(this);
    edit2 = new QLineEdit(this);
    edit3 = new QLineEdit(this);
    edit4 = new QComboBox(this);
    edit5 = new QLineEdit(this);
    confirmBtn = new QPushButton(tr("CONFIRM"), this);

    label1->setObjectName("CCRLabel1");
    label2->setObjectName("CCRLabel2");
    label3->setObjectName("CCRLabel3");
    label4->setObjectName("CCRLabel4");
    label5->setObjectName("CCRLabel5");
    edit1->setObjectName("CCREdit1");
    edit2->setObjectName("CCREdit2");
    edit3->setObjectName("CCREdit3");
    edit4->setObjectName("CCREdit4");
    edit5->setObjectName("CCREdit5");
    confirmBtn->setObjectName("CCRConfirmBtn");

    edit2->setEnabled(false);
    edit3->setEnabled(false);

    edit1->addItem("1231 2312 3123 1236");
    edit1->addItem("2175 7962 4595 4698");
    WDelegate *CCRDele1 = new WDelegate();
    edit1->setItemDelegate(CCRDele1);

    edit4->addItem("1231 2312 3123 1236");
    edit4->addItem("2175 7962 4595 4698");
    WDelegate *CCRDele2 = new WDelegate();
    edit4->setItemDelegate(CCRDele2);

    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(24, 140, 200, 24));
    label3->setGeometry(QRect(24, 188, 200, 24));
    label4->setGeometry(QRect(24, 236, 200, 24));
    label5->setGeometry(QRect(24, 284, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    edit2->setGeometry(QRect(288, 136, 400, 32));
    edit3->setGeometry(QRect(288, 184, 400, 32));
    edit4->setGeometry(QRect(288, 232, 400, 32));
    edit5->setGeometry(QRect(288, 280, 400, 32));
    confirmBtn->setGeometry(QRect(584, 336, 108, 36));
}

void CardRepayPage::updateLanguage()
{
    mainTitle->setText(tr("Credit Card Repay"));
    label1->setText(tr("Card number"));
    label2->setText(tr("Total repay amount"));
    label3->setText(tr("Minimum repay amount"));
    label4->setText(tr("Repay account"));
    label5->setText(tr("Repay ammount"));
    confirmBtn->setText(tr("CONFIRM"));
}

CardLostPage::CardLostPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("Credit Card Loss Report"));
    label1 = new QLabel(tr("Card number"), this);
    edit1 = new QComboBox(this);
    reportBtn = new QPushButton(tr("REPORT"), this);

    label1->setObjectName("CCLLabel1");
    edit1->setObjectName("CCLEdit1");
    reportBtn->setObjectName("CCLReportBtn");

    edit1->addItem("1231 2312 3123 1236");
    edit1->addItem("2175 7962 4595 4698");
    WDelegate *CCLDele = new WDelegate();
    edit1->setItemDelegate(CCLDele);

    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    reportBtn->setGeometry(QRect(584, 144, 108, 36));
}

void CardLostPage::updateLanguage()
{
    mainTitle->setText(tr("Credit Card Loss Report"));
    label1->setText(tr("Card number"));
    reportBtn->setText(tr("REPORT"));
}

UserInfoPage::UserInfoPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("Personal Info"));
    label1 = new QLabel(tr("Name"), this);
    label2 = new QLabel(tr("ID number"), this);
    label3 = new QLabel(tr("Activate date"), this);
    label4 = new QLabel(tr("Mobile"), this);
    label5 = new QLabel(tr("E-mail"), this);
    label6 = new QLabel(tr("Address"), this);
    label7 = new QLabel(tr("Zipcode"), this);
    edit1 = new QLineEdit(this);
    edit2 = new QLineEdit(this);
    edit3 = new QLineEdit(this);
    edit4 = new QLineEdit(this);
    edit5 = new QLineEdit(this);
    edit6 = new QLineEdit(this);
    edit7 = new QLineEdit(this);

    label1->setObjectName("CUILabel1");
    label2->setObjectName("CUILabel2");
    label3->setObjectName("CUILabel3");
    label4->setObjectName("CUILabel4");
    label5->setObjectName("CUILabel5");
    label4->setObjectName("CUILabel6");
    label5->setObjectName("CUILabel7");
    edit1->setObjectName("CUIEdit1");
    edit2->setObjectName("CUIEdit2");
    edit3->setObjectName("CUIEdit3");
    edit4->setObjectName("CUIEdit4");
    edit5->setObjectName("CUIEdit5");
    edit6->setObjectName("CUIEdit6");
    edit7->setObjectName("CUIEdit7");

    edit1->setEnabled(false);
    edit2->setEnabled(false);
    edit3->setEnabled(false);
    edit4->setEnabled(false);
    edit5->setEnabled(false);
    edit6->setEnabled(false);
    edit7->setEnabled(false);

    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(24, 140, 200, 24));
    label3->setGeometry(QRect(24, 188, 200, 24));
    label4->setGeometry(QRect(24, 236, 200, 24));
    label5->setGeometry(QRect(24, 284, 200, 24));
    label6->setGeometry(QRect(24, 332, 200, 24));
    label7->setGeometry(QRect(24, 380, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    edit2->setGeometry(QRect(288, 136, 400, 32));
    edit3->setGeometry(QRect(288, 184, 400, 32));
    edit4->setGeometry(QRect(288, 232, 400, 32));
    edit5->setGeometry(QRect(288, 280, 400, 32));
    edit6->setGeometry(QRect(288, 336, 400, 32));
    edit7->setGeometry(QRect(288, 384, 400, 32));
}

void UserInfoPage::updateLanguage()
{
    mainTitle->setText(tr("Personal Info"));
    label1->setText(tr("Name"));
    label2->setText(tr("ID number"));
    label3->setText(tr("Activate date"));
    label4->setText(tr("Mobile"));
    label5->setText(tr("E-mail"));
    label6->setText(tr("Address"));
    label7->setText(tr("Zipcode"));
}

ChangePwPage::ChangePwPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("Change Password"));
    label1 = new QLabel(tr("Original password"), this);
    label2 = new QLabel(tr("New password"), this);
    label3 = new QLabel(tr("Confirm password"), this);
    edit1 = new QLineEdit(this);
    edit2 = new QLineEdit(this);
    edit3 = new QLineEdit(this);
    confirmBtn = new QPushButton(tr("CONFIRM"), this);

    label1->setObjectName("CCPLabel1");
    label2->setObjectName("CCPLabel2");
    label3->setObjectName("CCPLabel3");
    edit1->setObjectName("CCPEdit1");
    edit2->setObjectName("CCPEdit2");
    edit3->setObjectName("CCPEdit3");
    confirmBtn->setObjectName("CCPConfirmBtn");

    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(24, 140, 200, 24));
    label3->setGeometry(QRect(24, 188, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    edit2->setGeometry(QRect(288, 136, 400, 32));
    edit3->setGeometry(QRect(288, 184, 400, 32));
    confirmBtn->setGeometry(QRect(584, 240, 108, 36));
}

void ChangePwPage::updateLanguage()
{
    mainTitle->setText(tr("Change Password"));
    label1->setText(tr("Original password"));
    label2->setText(tr("New password"));
    label3->setText(tr("Confirm password"));
    confirmBtn->setText(tr("CONFIRM"));
}

SysMsgPage::SysMsgPage(QWidget *parent) : WPage(parent)
{
    bgLabel = new QLabel(this);
    mainTitle->setText(tr("System Message"));
    table = new QTableWidget(this);

    bgLabel->setObjectName("CSMbg");
    table->setObjectName("CSMTable");

    bgLabel->setGeometry(QRect(0, 0, 751, 566));
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    table->setGeometry(QRect(24, 72, 708, 480));

    table->setColumnCount(3);
    table->setRowCount(5);

    QStringList headers;
    headers << "ID" << "Name" << "Age" << "Sex";
    table->setHorizontalHeaderLabels(headers);

    table->setItem(0, 0, new QTableWidgetItem(QString("0001")));
    table->setItem(1, 0, new QTableWidgetItem(QString("0002")));
    table->setItem(2, 0, new QTableWidgetItem(QString("0003")));
    table->setItem(3, 0, new QTableWidgetItem(QString("0004")));
    table->setItem(4, 0, new QTableWidgetItem(QString("0005")));
    table->setItem(5, 0, new QTableWidgetItem(QString("0006")));
    table->setItem(0, 1, new QTableWidgetItem(QString("20100112")));

    WDelegate *CSMDele = new WDelegate();
    table->setItemDelegate(CSMDele);

    table->verticalHeader()->hide();
    table->horizontalHeader()->setStretchLastSection(true);
    table->setShowGrid(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->resizeSection(0, 150);
    table->verticalHeader()->setDefaultSectionSize(48);
}

void SysMsgPage::updateLanguage()
{
    mainTitle->setText(tr("System Message"));
}

AboutPage::AboutPage(QWidget *parent) : WPage(parent)
{
    mainTitle->setText(tr("About"));
    label1 = new QTextEdit(this);
    label1->setText(tr("    This program is designed and developed by "
                       "Tsinghua freshman, Zhu Yilin and Tian Xingyu. "
                       "It serves as the big assignment for C++ course "
                       "taught by Prof. Dong. The develop environment is "
                       "Qt 5.5.0 MSVC2012 with Microsoft Visual C++ "
                       "Compiler 11.0 (x86).\n"
                       "    Here we extend special thanks to the course "
                       "teacher and TA, who lead us into the world of C++. "
                       "We would also like to offer thanks to the open "
                       "source projects that make our program possible."));

    label1->setEnabled(false);
    label1->setObjectName("CALabel1");

    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 708, 200));
}

void AboutPage::updateLanguage()
{
    mainTitle->setText(tr("About"));
    label1->setText(tr("    This program is designed and developed by "
                       "Tsinghua freshman, Zhu Yilin and Tian Xingyu. "
                       "It serves as the big assignment for C++ course "
                       "taught by Prof. Dong. The develop environment is "
                       "Qt 5.5.0 MSVC2012 with Microsoft Visual C++ "
                       "Compiler 11.0 (x86).\n"
                       "    Here we extend special thanks to the course "
                       "teacher and TA, who lead us into the world of C++. "
                       "We would also like to offer thanks to the open "
                       "source projects that make our program possible."));
}
