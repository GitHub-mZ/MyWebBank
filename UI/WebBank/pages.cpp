#include "wdelegate.h"
#include "pages.h"
#include "wmsgbox.h"
#include "wuimanip.h"
#include <QHeaderView>
#include <QListWidget>
#include <QToolButton>
#include <QTime>
#include <QDebug>
#include <QCryptographicHash>
#include <QFileDialog>
#include <QDir>
#include <QAxObject>
#include <QLinearGradient>
#include "qcustomplot.h"

WPage::WPage(QWidget *parent): QWidget(parent)
{
    //set common main title
    mainTitle = new QLabel(this);
    mainTitle->setObjectName("Title");
}

MyAccountPage::MyAccountPage(QWidget *parent) : WPage(parent)
{
    //components new
    bgLabel = new QLabel(this);
    mainTitle->setText(tr("My Account"));
    title2 = new QLabel(tr("Recent Transaction Records"), this);
    table1 = new QTableWidget(this);
    table2 = new QTableWidget(this);
    plotBtn = new QPushButton(tr("Show Statistics"), this);

    //set object name
    bgLabel->setObjectName("CMAbg");
    title2->setObjectName("CMALabel2");
    table1->setObjectName("CMATable1");
    table2->setObjectName("CMATable2");
    plotBtn->setObjectName("CMAPlot");

    //set position and size
    bgLabel->setGeometry(QRect(0, 0, 751, 566));
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    title2->setGeometry(QRect(24, 280, 708, 48));
    table1->setGeometry(QRect(24, 72, 708, 192));
    table2->setGeometry(QRect(24, 336, 708, 192));
    plotBtn->setGeometry(QRect(568, 24, 168, 36));

    //set connections
    connect(table1, SIGNAL(cellClicked(int, int)), this, SLOT(showAccountRecord(int, int)));
    connect(plotBtn, SIGNAL(clicked(bool)), parent->parent(), SLOT(showPlotPage()));
}

void MyAccountPage::setTable()
{
    //setup table1
    int accountNum = WUIManip::getAccountNum();
    table1->clear();
    table1->setColumnCount(5);
    table1->setRowCount(accountNum);

    //setup table headers
    QStringList header1;
    header1 << tr("Card Type")
            << tr("Card Number")
            << tr("Fixed")
            << tr("Deposit")
            << tr("Status");
    table1->setHorizontalHeaderLabels(header1);
    table1->horizontalHeader()->resizeSection(0, 140);
    table1->horizontalHeader()->resizeSection(1, 210);
    table1->horizontalHeader()->resizeSection(2, 120);
    table1->horizontalHeader()->resizeSection(3, 120);

    //set table contents
    for (int i = 0; i < accountNum; ++i)
    {
        QVector<QString> accountInfo = WUIManip::getAccountInfo(i);
        for (int j = 0; j < 5; ++j)
        {
            if (j == 0)
            {
                QString accountType;
                if (accountInfo[0] == "normalAccount")
                {
                    accountType = tr("Normal Account");
                }
                else if (accountInfo[0] == "platinumCard")
                {
                    accountType = tr("Platinum Card");
                }
                else if (accountInfo[0] == "goldCard")
                {
                    accountType = tr("Gold Card");
                }
                else if (accountInfo[0] == "silverCard")
                {
                    accountType = tr("Silver Card");
                }
                else if (accountInfo[0] == "normalCard")
                {
                    accountType = tr("Normal Card");
                }
                QTableWidgetItem *item = new QTableWidgetItem(accountType);
                table1->setItem(i, j, item);
            }
            else if (j == 4)
            {
                QString accountType;
                if (accountInfo[4] == "normal")
                {
                    accountType = tr("Normal");
                }
                else if (accountInfo[4] == "frozen")
                {
                    accountType = tr("Frozen");
                }
                QTableWidgetItem *item = new QTableWidgetItem(accountType);
                table1->setItem(i, j, item);
            }
            else
            {
                table1->setItem(i, j, new QTableWidgetItem(accountInfo[j]));
            }
            if (j == 0 || j == 1 || j == 4)
            {
                table1->item(i, j)->setTextAlignment(Qt::AlignCenter);
            }
            else
            {
                table1->item(i, j)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            }
        }
    }

    //set table delegate
    WDelegate *CMADele1 = new WDelegate();
    table1->setItemDelegate(CMADele1);

    //set table style
    table1->verticalHeader()->hide();
    table1->horizontalHeader()->setStretchLastSection(true);
    table1->setShowGrid(false);
    table1->setSelectionBehavior(QAbstractItemView::SelectRows);
    table1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table1->horizontalHeader()->setHighlightSections(false);
    table1->verticalHeader()->setDefaultSectionSize(48);

    //setup table2
    table2->clear();
    QVector<QString> recordInfo = WUIManip::getAccountRecord(0);
    table2->setColumnCount(3);
    table2->setRowCount(recordInfo.size() / 3);

    //set table
    QStringList header2;
    header2 << tr("Amount") << tr("Time") << tr("Transaction Type");
    table2->setHorizontalHeaderLabels(header2);
    table2->horizontalHeader()->resizeSection(0, 100);
    table2->horizontalHeader()->resizeSection(1, 250);

    for (int i = 0; i < recordInfo.size() / 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (j == 2)
            {
                QString transferType;
                if (recordInfo[3 * i + 2] == "Water")
                {
                    transferType = tr("Water");
                }
                else if (recordInfo[3 * i + 2] == "Gas")
                {
                    transferType = tr("Gas");
                }
                else if (recordInfo[3 * i + 2] == "Electricity")
                {
                    transferType = tr("Electricity");
                }
                else if (recordInfo[3 * i + 2] == "Transfer to Others")
                {
                    transferType = tr("Transfer to Others");
                }
                else if (recordInfo[3 * i + 2] == "Transfer to Current")
                {
                    transferType = tr("Transfer to Current");
                }
                else if (recordInfo[3 * i + 2] == "Transfer to Fixed")
                {
                    transferType = tr("Transfer to Fixed");
                }
                else if (recordInfo[3 * i + 2] == "Transfer from Others")
                {
                    transferType = tr("Transfer from Others");
                }
                QTableWidgetItem *item = new QTableWidgetItem(transferType);
                table2->setItem(i, j, item);
            }
            else
            {
                table2->setItem(i, j, new QTableWidgetItem(recordInfo[3 * i + j]));
            }
            if (j != 0)
            {
                table2->item(i, j)->setTextAlignment(Qt::AlignCenter);
            }
            else
            {
                table2->item(i, j)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            }
        }
    }

    WDelegate *CMADele2 = new WDelegate();
    table2->setItemDelegate(CMADele2);

    table2->verticalHeader()->hide();
    table2->horizontalHeader()->setStretchLastSection(true);
    table2->setShowGrid(false);
    table2->setSelectionBehavior(QAbstractItemView::SelectRows);
    table2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table2->horizontalHeader()->setHighlightSections(false);
    table2->verticalHeader()->setDefaultSectionSize(48);
}

void MyAccountPage::showAccountRecord(int row, int column)
{
    QVector<QString> recordInfo = WUIManip::getAccountRecord(row);
    column;
    table2->setRowCount(recordInfo.size() / 3);
    table2->clearContents();
    for (int i = 0; i < recordInfo.size() / 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (j == 2)
            {
                QString transferType;
                if (recordInfo[3 * i + 2] == "Water")
                {
                    transferType = tr("Water");
                }
                else if (recordInfo[3 * i + 2] == "Gas")
                {
                    transferType = tr("Gas");
                }
                else if (recordInfo[3 * i + 2] == "Electricity")
                {
                    transferType = tr("Electricity");
                }
                else if (recordInfo[3 * i + 2] == "Transfer to Others")
                {
                    transferType = tr("Transfer to Others");
                }
                else if (recordInfo[3 * i + 2] == "Transfer to Current")
                {
                    transferType = tr("Transfer to Current");
                }
                else if (recordInfo[3 * i + 2] == "Transfer to Fixed")
                {
                    transferType = tr("Transfer to Fixed");
                }
                else if (recordInfo[3 * i + 2] == "Transfer from Others")
                {
                    transferType = tr("Transfer from Others");
                }
                QTableWidgetItem *item = new QTableWidgetItem(transferType);
                table2->setItem(i, j, item);
            }
            else
            {
                table2->setItem(i, j, new QTableWidgetItem(recordInfo[3 * i + j]));
            }
            if (j != 0)
            {
                table2->item(i, j)->setTextAlignment(Qt::AlignCenter);
            }
            else
            {
                table2->item(i, j)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            }
        }
    }
}

void MyAccountPage::updateLanguage()
{
    //update language in this page
    mainTitle->setText(tr("My Account"));
    title2->setText(tr("Recent Transaction Records"));
    plotBtn->setText(tr("Show Statistics"));

    QStringList header1;
    header1 << tr("Card Type")
            << tr("Card Number")
            << tr("Fixed")
            << tr("Deposit")
            << tr("Status");
    table1->setHorizontalHeaderLabels(header1);

    QStringList header2;
    header2 << tr("Amount") << tr("Time") << tr("Transaction Type");
    table2->setHorizontalHeaderLabels(header2);
    this->setTable();
}

AccountQueryPage::AccountQueryPage(QWidget *parent) : WPage(parent)
{
    //components new
    bgLabel = new QLabel(this);
    mainTitle->setText(tr("Account Query"));

    label1 = new QLabel(tr("Account"), this);
    label2 = new QLabel(tr("Date range"), this);
    accountBox = new QComboBox(this);
    incomeCkBox = new QCheckBox(tr("Income"), this);
    expenseCkBox = new QCheckBox(tr("Expense"), this);
    searchBtn = new QPushButton(tr("SEARCH"), this);
    recentBtn = new QPushButton(tr("Recent Three Months"), this);
    exportBtn = new QPushButton(tr("EXPORT"), this);
    fromDate = new WLineEdit(this);
    toDate = new WLineEdit(this);
    table = new QTableWidget(this);
    calendarLabel = new QLabel(this);
    calendar1 = new QCalendarWidget(this);
    calendar1->setGridVisible(false);
    calendar2 = new QCalendarWidget(this);
    calendar2->setGridVisible(false);

    //set object name
    bgLabel->setObjectName("CAQbg");
    label1->setObjectName("CAQLabel");
    label2->setObjectName("CAQDate");
    accountBox->setObjectName("CAQAccount");
    incomeCkBox->setObjectName("CAQIncome");
    expenseCkBox->setObjectName("CAQExpense");
    searchBtn->setObjectName("CAQSearch");
    recentBtn->setObjectName("CAQRecent");
    exportBtn->setObjectName("CAQExport");
    fromDate->setObjectName("CAQFrom");
    toDate->setObjectName("CAQTo");
    table->setObjectName("CAQTable");
    calendarLabel->setObjectName("calendarLabel");

    //set position and size
    bgLabel->setGeometry(QRect(0, 0, 751, 566));
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(368, 92, 100, 24));
    accountBox->setGeometry(QRect(124, 92, 200, 24));
    incomeCkBox->setGeometry(QRect(24, 140, 100, 24));
    expenseCkBox->setGeometry(QRect(130, 140, 100, 24));
    searchBtn->setGeometry(QRect(516, 134, 100, 36));
    recentBtn->setGeometry(QRect(278, 134, 220, 36));
    exportBtn->setGeometry(QRect(632, 134, 100, 36));
    fromDate->setGeometry(QRect(486, 92, 108, 24));
    toDate->setGeometry(QRect(624, 92, 108, 24));
    table->setGeometry(QRect(24, 192, 708, 336));
    calendarLabel->setGeometry(QRect(360, 120, 380, 100));
    calendar1->move(QPoint(350, 120));
    calendar2->move(QPoint(360, 120));

    //setup calendar
    calendar1->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendar1->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
    calendar1->setStyleSheet("font:16px;");
    calendar2->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendar2->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
    calendar2->setStyleSheet("font:16px;");

    calendar1->setVisible(false);
    calendar2->setVisible(false);
    calendarLabel->setVisible(false);

    //setup date edit
    queryType = -1;
    fromDate->setPlaceholderText("YYYY.MM.DD");
    toDate->setPlaceholderText("YYYY.MM.DD");
    QRegExp dateRestriction("[1-2][0-9]{3}\\.[0-9]{1,2}\\.[0-9]{1,2}");
    toDate->setValidator(new QRegExpValidator(dateRestriction, this));
    fromDate->setValidator(new QRegExpValidator(dateRestriction, this));

    //set connections
    connect(fromDate, SIGNAL(Wclicked()), this, SLOT(showCalendar1()));
    connect(calendar1, SIGNAL(clicked(QDate)), this, SLOT(setCalendar1()));
    connect(toDate, SIGNAL(Wclicked()), this, SLOT(showCalendar2()));
    connect(calendar2, SIGNAL(clicked(QDate)), this, SLOT(setCalendar2()));
    connect(incomeCkBox, SIGNAL(clicked(bool)), this, SLOT(popExpense()));
    connect(expenseCkBox, SIGNAL(clicked(bool)), this, SLOT(popIncome()));
    connect(searchBtn, SIGNAL(clicked(bool)), this, SLOT(search()));
    connect(recentBtn, SIGNAL(clicked(bool)), this, SLOT(recent()));
    connect(exportBtn, SIGNAL(clicked(bool)), this, SLOT(exportExcel()));
}

void AccountQueryPage::setTable()
{
    //setup table
    table->clear();
    table->setColumnCount(3);
    table->setRowCount(5);

    QStringList header;
    header << tr("Amount") << tr("Time") << tr("Transaction Type");
    table->setHorizontalHeaderLabels(header);
    table->horizontalHeader()->resizeSection(0, 100);
    table->horizontalHeader()->resizeSection(1, 250);
    WDelegate *CAQDele = new WDelegate();
    table->setItemDelegate(CAQDele);
    table->verticalHeader()->hide();
    table->horizontalHeader()->setStretchLastSection(true);
    table->setShowGrid(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->setHighlightSections(false);
    table->verticalHeader()->setDefaultSectionSize(48);
}

void AccountQueryPage::setComboBox()
{
    calendar1->setVisible(false);
    calendar2->setVisible(false);
    calendarLabel->setVisible(false);
    //setup accounts
    accountBox->clear();
    int accountNum = WUIManip::getAccountNum();
    for (int i = 0; i < accountNum; ++i)
    {
        QVector<QString> accounts = WUIManip::getAccountInfo(i);
        accountBox->addItem(accounts[1]);
    }
    WDelegate *CMADele = new WDelegate();
    accountBox->setItemDelegate(CMADele);
}

void AccountQueryPage::search()
{
    QVector<QString> records;
    if (fromDate->text().length() == 0 || toDate->text().length() == 0)
    {
        if (incomeCkBox->isChecked() && !expenseCkBox->isChecked())
        {
            queryType = 1;
            records = WUIManip::query(1, accountBox->currentText());
        }
        else if (!incomeCkBox->isChecked() && expenseCkBox->isChecked())
        {
            queryType = 2;
            records = WUIManip::query(2, accountBox->currentText());
        }
        else
        {
            queryType = 0;
            records = WUIManip::query(0, accountBox->currentText());
        }
    }
    else
    {
        QDate from, to, temp;
        from = temp.fromString(fromDate->text(), "yyyy.MM.dd");
        to = temp.fromString(toDate->text(), "yyyy.MM.dd");
        if (incomeCkBox->isChecked() && !expenseCkBox->isChecked())
        {
            queryType = 4;
            records = WUIManip::dateQuery(1, accountBox->currentText(), from, to);
        }
        else if (!incomeCkBox->isChecked() && expenseCkBox->isChecked())
        {
            queryType = 5;
            records = WUIManip::dateQuery(2, accountBox->currentText(), from, to);
        }
        else
        {
            queryType = 3;
            records = WUIManip::dateQuery(0, accountBox->currentText(), from, to);
        }
    }
    table->setRowCount(records.size() / 3);
    table->clearContents();
    for (int i = 0; i < records.size() / 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (j == 2)
            {
                QString transferType;
                if (records[3 * i + 2] == "Water")
                {
                    transferType = tr("Water");
                }
                else if (records[3 * i + 2] == "Gas")
                {
                    transferType = tr("Gas");
                }
                else if (records[3 * i + 2] == "Electricity")
                {
                    transferType = tr("Electricity");
                }
                else if (records[3 * i + 2] == "Transfer to Others")
                {
                    transferType = tr("Transfer to Others");
                }
                else if (records[3 * i + 2] == "Transfer to Current")
                {
                    transferType = tr("Transfer to Current");
                }
                else if (records[3 * i + 2] == "Transfer to Fixed")
                {
                    transferType = tr("Transfer to Fixed");
                }
                else if (records[3 * i + 2] == "Transfer from Others")
                {
                    transferType = tr("Transfer from Others");
                }
                QTableWidgetItem *item = new QTableWidgetItem(transferType);
                table->setItem(i, j, item);
            }
            else
            {
                table->setItem(i, j, new QTableWidgetItem(records[3 * i + j]));
            }
            if (j != 0)
            {
                table->item(i, j)->setTextAlignment(Qt::AlignCenter);
            }
            else
            {
                table->item(i, j)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            }
        }
    }
}

void AccountQueryPage::recent()
{
    QVector<QString> records;
    if (incomeCkBox->isChecked() && !expenseCkBox->isChecked())
    {
        queryType = 7;
        records = WUIManip::query(8, accountBox->currentText());
    }
    else if (!incomeCkBox->isChecked() && expenseCkBox->isChecked())
    {
        queryType = 8;
        records = WUIManip::query(16, accountBox->currentText());
    }
    else
    {
        queryType = 6;
        records = WUIManip::query(4, accountBox->currentText());
    }
    QStringList header;
    table->setRowCount(records.size() / 3);
    table->clearContents();
    for (int i = 0; i < records.size() / 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (j == 2)
            {
                QString transferType;
                if (records[3 * i + 2] == "Water")
                {
                    transferType = tr("Water");
                }
                else if (records[3 * i + 2] == "Gas")
                {
                    transferType = tr("Gas");
                }
                else if (records[3 * i + 2] == "Electricity")
                {
                    transferType = tr("Electricity");
                }
                else if (records[3 * i + 2] == "Transfer to Others")
                {
                    transferType = tr("Transfer to Others");
                }
                else if (records[3 * i + 2] == "Transfer to Current")
                {
                    transferType = tr("Transfer to Current");
                }
                else if (records[3 * i + 2] == "Transfer to Fixed")
                {
                    transferType = tr("Transfer to Fixed");
                }
                else if (records[3 * i + 2] == "Transfer from Others")
                {
                    transferType = tr("Transfer from Others");
                }
                QTableWidgetItem *item = new QTableWidgetItem(transferType);
                table->setItem(i, j, item);
            }
            else
            {
                table->setItem(i, j, new QTableWidgetItem(records[3 * i + j]));
            }
            if (j != 0)
            {
                table->item(i, j)->setTextAlignment(Qt::AlignCenter);
            }
            else
            {
                table->item(i, j)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            }
        }
    }
}

void AccountQueryPage::exportExcel()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Records"), "." , "*.xls");
    if(filename.isEmpty())
    {
        WMsgBox::information(tr("Failed to get filename!"));
        return;
    }
    QAxObject *excel = new QAxObject("Excel.application");
    excel->dynamicCall("setVisible(bool)", false);
    excel->setProperty("Visible", false);
    QAxObject *workBooks = excel->querySubObject("WorkBooks");
    workBooks->dynamicCall("Add");
    QAxObject *workBook = excel->querySubObject("ActiveWorkBook");
    QAxObject *worksheet = workBook->querySubObject("WorkSheets(int)", 1);
    QVector<QString> records;
    QDate from, to, temp;
    switch(queryType)
    {
    case 0:
        records = WUIManip::query(0, accountBox->currentText());
        break;
    case 1:
        records = WUIManip::query(1, accountBox->currentText());
        break;
    case 2:
        records = WUIManip::query(2, accountBox->currentText());
        break;
    case 3:
        from = temp.fromString(fromDate->text(), "yyyy.MM.dd");
        to = temp.fromString(toDate->text(), "yyyy.MM.dd");
        records = WUIManip::dateQuery(0, accountBox->currentText(), from, to);
        break;
    case 4:
        from = temp.fromString(fromDate->text(), "yyyy.MM.dd");
        to = temp.fromString(toDate->text(), "yyyy.MM.dd");
        records = WUIManip::dateQuery(1, accountBox->currentText(), from, to);
        break;
    case 5:
        from = temp.fromString(fromDate->text(), "yyyy.MM.dd");
        to = temp.fromString(toDate->text(), "yyyy.MM.dd");
        records = WUIManip::dateQuery(2, accountBox->currentText(), from, to);
        break;
    case 6:
        records = WUIManip::query(4, accountBox->currentText());
        break;
    case 7:
        records = WUIManip::query(8, accountBox->currentText());
        break;
    case 8:
        records = WUIManip::query(16, accountBox->currentText());
        break;
    }
    records.push_front("Transaction Type");
    records.push_front("Time");
    records.push_front("Amount");
    for(int i = 0; i < records.size() / 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            QAxObject *range = worksheet->querySubObject("Cells(int,int)", i + 1, j + 1);
            range->setProperty("Value", records[3 * i + j]);
        }
    }
    workBook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filename));
    WMsgBox::information(tr("Successfully saved!"));
    workBook->dynamicCall("Close()");
    worksheet->clear();
    excel->dynamicCall("Quit()");
    delete excel;
}

void AccountQueryPage::popExpense()
{
    expenseCkBox->setChecked(false);
}

void AccountQueryPage::popIncome()
{
    incomeCkBox->setChecked(false);
}

void AccountQueryPage::showCalendar1()
{
    calendar1->setVisible(true);
    calendar2->setVisible(false);
    calendarLabel->setVisible(true);
}

void AccountQueryPage::showCalendar2()
{
    calendar1->setVisible(false);
    calendar2->setVisible(true);
    calendarLabel->setVisible(true);
}

void AccountQueryPage::setCalendar1()
{
    fromDate->setText(calendar1->selectedDate().toString("yyyy.MM.dd"));
    calendar1->setVisible(false);
    calendarLabel->setVisible(false);
}

void AccountQueryPage::setCalendar2()
{
    toDate->setText(calendar2->selectedDate().toString("yyyy.MM.dd"));
    calendar2->setVisible(false);
    calendarLabel->setVisible(false);
}

void AccountQueryPage::updateLanguage()
{
    //update language in this page
    mainTitle->setText(tr("Account Query"));
    label1->setText(tr("Account"));
    label2->setText(tr("Date Range"));
    incomeCkBox->setText(tr("Income"));
    expenseCkBox->setText(tr("Expense"));
    searchBtn->setText(tr("SEARCH"));
    recentBtn->setText(tr("Recent Three Months"));
    exportBtn->setText(tr("EXPORT"));

    QStringList header;
    header << tr("Amount") << tr("Time") << tr("Transaction Type");
    table->setHorizontalHeaderLabels(header);
    this->setTable();
    this->recent();
}

TransferPage::TransferPage(QWidget *parent) : WPage(parent)
{
    //components new
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

    //set object name
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

    //set position and size
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

    connect(confirmBtn, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void TransferPage::setComboBox()
{
    //setup accounts
    edit1->clear();
    int accountNum = WUIManip::getAccountNum();
    for (int i = 0; i < accountNum; ++i)
    {
        QVector<QString> accounts = WUIManip::getAccountInfo(i);
        edit1->addItem(accounts[1]);
    }
    WDelegate *CTDele = new WDelegate();
    edit1->setItemDelegate(CTDele);
}

void TransferPage::confirm()
{
    if (edit2->text().length() == 0)
    {
        WMsgBox::information(tr("Receiver's Name Empty!"));
        return;
    }
    if (edit3->text().length() != 19)
    {
        WMsgBox::information(tr("Receiver's Account Invalid!"));
        return;
    }
    QByteArray ba = edit3->text().toLatin1();
    const char *s = ba.data();
    while(*s && *s >= '0' && *s <= '9') s++;
    if (*s)
    {
        WMsgBox::information(tr("Receiver's Account Invalid!"));
        return;
    }
    if (edit4->text().toFloat() <= 0)
    {
        WMsgBox::information(tr("Amount Invalid!"));
        return;
    }
    bool val = WUIManip::transfer(edit1->currentText(), edit3->text(), edit4->text());
    if (val)
        WMsgBox::information(tr("Transfer Success!"));
    else
        WMsgBox::information(tr("Transfer Failed!"));
}

void TransferPage::updateLanguage()
{
    //update language in this page
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
    //components new
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

    //set object name
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

    edit4->addItem(tr("Current to Fix"));
    edit4->addItem(tr("Fix to Current"));
    WDelegate *CCFDele2 = new WDelegate();
    edit4->setItemDelegate(CCFDele2);

    //set position and size
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

    connect(edit1, SIGNAL(currentIndexChanged(QString)), edit3, SLOT(setText(QString)));
    connect(confirmBtn, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void CurrentFixPage::setComboBox()
{
    //setup accounts
    edit1->clear();
    int accountNum = WUIManip::getAccountNum();
    for (int i = 0; i < accountNum; ++i)
    {
        QVector<QString> accounts = WUIManip::getAccountInfo(i);
        if (accounts[0] == "normalAccount")
        {
            edit1->addItem(accounts[1]);
        }
    }

    WDelegate *CCFDele1 = new WDelegate();
    edit1->setItemDelegate(CCFDele1);

    edit3->setText(edit1->currentText());
}

void CurrentFixPage::confirm()
{
    edit3->setText(edit1->currentText());
    if (edit2->text().length() == 0)
    {
        WMsgBox::information(tr("Receiver's Name Empty!"));
        return;
    }
    if (edit3->text().length() != 19)
    {
        WMsgBox::information(tr("Receiver's Account Invalid!"));
        return;
    }
    QByteArray ba = edit3->text().toLatin1();
    const char *s = ba.data();
    while(*s && *s >= '0' && *s <= '9') s++;
    if (*s)
    {
        WMsgBox::information(tr("Receiver's Account Invalid!"));
        return;
    }
    if (edit5->text().toFloat() <= 0)
    {
        WMsgBox::information(tr("Amount Invalid!"));
        return;
    }
    bool val = WUIManip::currentFix(edit4->currentIndex(), edit1->currentText(), edit3->text(), edit5->text());
    if (val)
        WMsgBox::information(tr("Exchange Success!"));
    else
        WMsgBox::information(tr("Exchange Failed!"));
}

void CurrentFixPage::updateLanguage()
{
    //update language in this page
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
    //components new
    mainTitle->setText(tr("Payment"));
    label1 = new QLabel(tr("Item"), this);
    label2 = new QLabel(tr("Paying account"), this);
    label3 = new QLabel(tr("Due"), this);
    edit1 = new QComboBox(this);
    edit2 = new QComboBox(this);
    edit3 = new QLineEdit(this);
    autoBtn = new QPushButton(tr("SET AUTOPAY"), this);
    confirmBtn = new QPushButton(tr("CONFIRM"), this);

    //set object name
    label1->setObjectName("CPLabel1");
    label2->setObjectName("CPLabel2");
    label3->setObjectName("CPLabel3");
    edit1->setObjectName("CPEdit1");
    edit2->setObjectName("CPEdit2");
    edit3->setObjectName("CPEdit3");
    autoBtn->setObjectName("CPAutoBtn");
    confirmBtn->setObjectName("CPConfirmBtn");

    //setup item
    edit3->setEnabled(false);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    for (int i = 0; i < 3; ++i)
    {
        value[i] = qrand() % 100 + 100;
    }
    edit3->setText(QString::number(value[0]));
    edit1->addItem(tr("Water Bill"));
    edit1->addItem(tr("Electricity Bill"));
    edit1->addItem(tr("Gas Bill"));
    WDelegate *CPDele1 = new WDelegate();
    edit1->setItemDelegate(CPDele1);

    //set position and size
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(24, 140, 200, 24));
    label3->setGeometry(QRect(24, 188, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    edit2->setGeometry(QRect(288, 136, 400, 32));
    edit3->setGeometry(QRect(288, 184, 400, 32));
    autoBtn->setGeometry(QRect(430, 240, 148, 36));
    confirmBtn->setGeometry(QRect(584, 240, 108, 36));

    //set connections to autopay page
    connect(autoBtn, SIGNAL(clicked(bool)), parent->parent(), \
            SLOT(showAutoPayPage()));
    connect(edit1, SIGNAL(currentIndexChanged(int)), this, SLOT(changeValue(int)));
    connect(confirmBtn, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void PaymentPage::setComboBox()
{
    //setup accounts
    edit2->clear();
    int accountNum = WUIManip::getAccountNum();
    for (int i = 0; i < accountNum; ++i)
    {
        QVector<QString> accounts = WUIManip::getAccountInfo(i);
        edit2->addItem(accounts[1]);
    }

    WDelegate *CPDele2 = new WDelegate();
    edit2->setItemDelegate(CPDele2);
}

void PaymentPage::confirm()
{
    QString type;
    switch(edit1->currentIndex())
    {
    case 0:
        type = "Water";
        break;
    case 1:
        type = "Electricity";
        break;
    case 2:
        type = "Gas";
        break;
    }
    bool val = WUIManip::payment(type, edit2->currentText(), edit3->text());
    if (val)
        WMsgBox::information(tr("Pay Success!"));
    else
        WMsgBox::information(tr("Pay Failed!"));
}

void PaymentPage::changeValue(int i)
{
    edit3->setText(QString::number(value[i]));
}

void PaymentPage::updateLanguage()
{
    //update language in this page
    mainTitle->setText(tr("Payment"));
    label1->setText(tr("Item"));
    label2->setText(tr("Paying account"));
    label3->setText(tr("Due"));
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
    //components new
    bgLabel = new QLabel(this);
    mainTitle->setText(tr("Auto Payment"));
    label1 = new QLabel(tr("Item"), this);
    label2 = new QLabel(tr("Paying account"), this);
    title2 = new QLabel(tr("Already Set Auto Payments"), this);
    edit1 = new QComboBox(this);
    edit2 = new QComboBox(this);
    settingBtn = new QPushButton(tr("SET"), this);
    cancelBtn = new QPushButton(tr("CANCEL"), this);
    table = new QTableWidget(this);

    //set object name
    bgLabel->setObjectName("CAPbg");
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

    //set position and size
    bgLabel->setGeometry(QRect(0, 0, 751, 566));
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(24, 140, 200, 24));
    title2->setGeometry(QRect(24, 232, 708, 48));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    edit2->setGeometry(QRect(288, 136, 400, 32));
    settingBtn->setGeometry(QRect(596, 192, 96, 36));
    cancelBtn->setGeometry(QRect(484, 192, 96, 36));
    table->setGeometry(QRect(24, 288, 708, 240));

    connect(settingBtn, SIGNAL(clicked(bool)), this, SLOT(setAutoPay()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(cancelAutoPay()));
    connect(settingBtn, SIGNAL(clicked(bool)), this, SLOT(updateTable()));
    connect(cancelBtn, SIGNAL(clicked(bool)), this, SLOT(updateTable()));
}

void AutoPayPage::setTable()
{
    //setup table
    QVector<QString> log = WUIManip::getAutopayRecord();
    table->clear();
    table->setColumnCount(2);
    table->setRowCount(log.size() / 3);

    QStringList headers;
    headers << tr("Account") << tr("Item");
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->resizeSection(0, 500);

    for (int i = 0; i < log.size() / 3; ++i)
    {
        table->setItem(i, 0, new QTableWidgetItem(log[3 * i]));

        QString accountType;
        if (log[3 * i + 1] == "Water")
        {
            accountType = tr("Water");
        }
        else if (log[3 * i + 1] == "Electricity")
        {
            accountType = tr("Electricity");
        }
        else if (log[3 * i + 1] == "Gas")
        {
            accountType = tr("Gas");
        }
        QTableWidgetItem *item = new QTableWidgetItem(accountType);
        table->setItem(i, 1, item);

        table->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        table->item(i, 1)->setTextAlignment(Qt::AlignCenter);
    }

    WDelegate *CAPDele = new WDelegate();
    table->setItemDelegate(CAPDele);

    table->verticalHeader()->hide();
    table->horizontalHeader()->setStretchLastSection(true);
    table->setShowGrid(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->resizeSection(0, 450);
    table->verticalHeader()->setDefaultSectionSize(48);
}

void AutoPayPage::setComboBox()
{
    //setup accounts
    edit2->clear();
    int accountNum = WUIManip::getAccountNum();
    for (int i = 0; i < accountNum; ++i)
    {
        QVector<QString> accounts = WUIManip::getAccountInfo(i);
        edit2->addItem(accounts[1]);
    }

    WDelegate *CAPDele2 = new WDelegate();
    edit2->setItemDelegate(CAPDele2);
}

void AutoPayPage::setAutoPay()
{
    QString type;
    switch(edit1->currentIndex())
    {
    case 0:
        type = "Water";
        break;
    case 1:
        type = "Electricity";
        break;
    case 2:
        type = "Gas";
        break;
    }
    bool val = WUIManip::setAutopay(edit2->currentText(), type);
    if (val)
        WMsgBox::information(tr("Autopay Set Success!"));
    else
        WMsgBox::information(tr("Autopay Set Failed!"));
}

void AutoPayPage::cancelAutoPay()
{
    QString type;
    switch(edit1->currentIndex())
    {
    case 0:
        type = "Water";
        break;
    case 1:
        type = "Electricity";
        break;
    case 2:
        type = "Gas";
        break;
    }
    bool val = WUIManip::cancelAutopay(edit2->currentText(), type);
    if (val)
        WMsgBox::information(tr("Autopay Cancel Success!"));
    else
        WMsgBox::information(tr("Autopay Cancel Failed!"));
}

void AutoPayPage::updateTable()
{
    QVector<QString> log = WUIManip::getAutopayRecord();
    table->setRowCount(log.size() / 3);
    table->clearContents();
    for (int i = 0; i < log.size() / 3; ++i)
    {
        table->setItem(i, 0, new QTableWidgetItem(log[3 * i]));

        QString accountType;
        if (log[3 * i + 1] == "Water")
        {
            accountType = tr("Water");
        }
        else if (log[3 * i + 1] == "Electricity")
        {
            accountType = tr("Electricity");
        }
        else if (log[3 * i + 1] == "Gas")
        {
            accountType = tr("Gas");
        }
        QTableWidgetItem *item = new QTableWidgetItem(accountType);
        table->setItem(i, 1, item);

        table->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        table->item(i, 1)->setTextAlignment(Qt::AlignCenter);
    }
}

void AutoPayPage::updateLanguage()
{
    //update language in this page
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
    this->setTable();
}

CardApplyPage::CardApplyPage(QWidget *parent) : WPage(parent)
{
    //components new
    mainTitle->setText(tr("Credit Card Apply"));
    label1 = new QLabel(tr("Card type"), this);
    edit1 = new QComboBox(this);
    confirmBtn = new QPushButton(tr("CONFIRM"), this);

    //set object name
    label1->setObjectName("CCALabel1");
    edit1->setObjectName("CCAEdit1");
    confirmBtn->setObjectName("CCAConfirmBtn");

    //setup combobox item
    edit1->addItem(tr("Platinum Card"));
    edit1->addItem(tr("Gold Card"));
    edit1->addItem(tr("Silver Card"));
    edit1->addItem(tr("Normal Card"));
    WDelegate *CCADele = new WDelegate();
    edit1->setItemDelegate(CCADele);

    //set position and size
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    confirmBtn->setGeometry(QRect(584, 144, 108, 36));

    connect(confirmBtn, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void CardApplyPage::confirm()
{
    bool val = WUIManip::cardApply(edit1->currentIndex());
    if (val)
        WMsgBox::information(tr("Apply Success!"));
    else
        WMsgBox::information(tr("Apply Failed!"));
}

void CardApplyPage::updateLanguage()
{
    //update language in this page
    mainTitle->setText(tr("Credit Card Apply"));
    label1->setText(tr("Card type"));
    confirmBtn->setText(tr("CONFIRM"));
    edit1->clear();
    edit1->addItem(tr("Platinum Card"));
    edit1->addItem(tr("Gold Card"));
    edit1->addItem(tr("Silver Card"));
    edit1->addItem(tr("Normal Card"));
    WDelegate *CCADele = new WDelegate();
    edit1->setItemDelegate(CCADele);
}

CardActivatePage::CardActivatePage(QWidget *parent) : WPage(parent)
{
    //components new
    mainTitle->setText(tr("Credit Card Activate"));
    label1 = new QLabel(tr("Card number"), this);
    edit1 = new QComboBox(this);
    activateBtn = new QPushButton(tr("ACTIVATE"), this);

    //set object name
    label1->setObjectName("CCBLabel1");
    edit1->setObjectName("CCBEdit1");
    activateBtn->setObjectName("CCBActivateBtn");

    //set position and size
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    activateBtn->setGeometry(QRect(584, 144, 108, 36));

    connect(activateBtn, SIGNAL(clicked(bool)), this, SLOT(activate()));
}

void CardActivatePage::setComboBox()
{
    //setup accounts
    edit1->clear();
    int accountNum = WUIManip::getAccountNum();
    for (int i = 0; i < accountNum; ++i)
    {
        QVector<QString> accounts = WUIManip::getAccountInfo(i);
        if (accounts[0] != "normalAccount")
        {
            edit1->addItem(accounts[1]);
        }
    }

    WDelegate *CCBDele = new WDelegate();
    edit1->setItemDelegate(CCBDele);
}

void CardActivatePage::activate()
{
    bool val = WUIManip::cardActivate(edit1->currentText());
    if (val)
        WMsgBox::information(tr("Activate Success!"));
    else
        WMsgBox::information(tr("Activate Failed!"));
}

void CardActivatePage::updateLanguage()
{
    //update language in this page
    mainTitle->setText(tr("Credit Card Activate"));
    label1->setText(tr("Card number"));
    activateBtn->setText(tr("ACTIVATE"));
}

CardRepayPage::CardRepayPage(QWidget *parent) : WPage(parent)
{
    //components new
    mainTitle->setText(tr("Credit Card Repay"));
    label1 = new QLabel(tr("Card number"), this);
    label2 = new QLabel(tr("Total due"), this);
    label3 = new QLabel(tr("Minimum due"), this);
    label4 = new QLabel(tr("Repay account"), this);
    label5 = new QLabel(tr("Repay ammount"), this);
    edit1 = new QComboBox(this);
    edit2 = new QLineEdit(this);
    edit3 = new QLineEdit(this);
    edit4 = new QComboBox(this);
    edit5 = new QLineEdit(this);
    confirmBtn = new QPushButton(tr("CONFIRM"), this);

    //set object name
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

    //set disable attribute
    edit2->setEnabled(false);
    edit3->setEnabled(false);
    QString val1, val2;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    float val = (qrand() % 9000 + 1000) / 10;
    val1.setNum(val);
    val2.setNum(val / 10);
    edit2->setText(val1);
    edit3->setText(val2);


    //set position and size
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

    connect(confirmBtn, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void CardRepayPage::setComboBox()
{
    //setup accounts
    edit1->clear();
    int accountNum = WUIManip::getAccountNum();
    for (int i = 0; i < accountNum; ++i)
    {
        QVector<QString> accounts = WUIManip::getAccountInfo(i);
        if (accounts[0] != "normalAccount")
        {
            edit1->addItem(accounts[1]);
        }
    }

    WDelegate *CCRDele1 = new WDelegate();
    edit1->setItemDelegate(CCRDele1);

    //setup accounts
    int CRAccountNum = WUIManip::getAccountNum();
    for (int i = 0; i < CRAccountNum; ++i)
    {
        QVector<QString> accounts = WUIManip::getAccountInfo(i);
        if (accounts[0] == "normalAccount")
        {
            edit4->addItem(accounts[1]);
        }
    }

    WDelegate *CCRDele2 = new WDelegate();
    edit4->setItemDelegate(CCRDele2);
}

void CardRepayPage::confirm()
{
    if (edit5->text().toFloat() < edit3->text().toFloat())
    {
        WMsgBox::information(tr("Amount Too Small!"));
        return;
    }
    if (edit5->text().toFloat() > edit2->text().toFloat())
    {
        WMsgBox::information(tr("Amount Too Large!"));
        return;
    }
    bool val = WUIManip::cardRepay(edit1->currentText(), edit4->currentText(), edit5->text());
    if (val)
        WMsgBox::information(tr("Transfer Success!"));
    else
        WMsgBox::information(tr("Transfer Failed!"));

}

void CardRepayPage::updateLanguage()
{
    //update language in this page
    mainTitle->setText(tr("Credit Card Repay"));
    label1->setText(tr("Card number"));
    label2->setText(tr("Total due"));
    label3->setText(tr("Minimum due"));
    label4->setText(tr("Repay account"));
    label5->setText(tr("Repay ammount"));
    confirmBtn->setText(tr("CONFIRM"));
}

CardLostPage::CardLostPage(QWidget *parent) : WPage(parent)
{
    //components new
    mainTitle->setText(tr("Credit Card Loss Report"));
    label1 = new QLabel(tr("Card number"), this);
    edit1 = new QComboBox(this);
    reportBtn = new QPushButton(tr("REPORT"), this);

    //set object name
    label1->setObjectName("CCLLabel1");
    edit1->setObjectName("CCLEdit1");
    reportBtn->setObjectName("CCLReportBtn");

    //set position and size
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    reportBtn->setGeometry(QRect(584, 144, 108, 36));

    connect(reportBtn, SIGNAL(clicked(bool)), this, SLOT(report()));
}

void CardLostPage::setComboBox()
{
    //setup accounts
    edit1->clear();
    int accountNum = WUIManip::getAccountNum();
    for (int i = 0; i < accountNum; ++i)
    {
        QVector<QString> accounts = WUIManip::getAccountInfo(i);
        if (accounts[0] != "normalAccount")
        {
            edit1->addItem(accounts[1]);
        }
    }

    WDelegate *CCLDele = new WDelegate();
    edit1->setItemDelegate(CCLDele);
}

void CardLostPage::report()
{
    bool val = WUIManip::cardLost(edit1->currentText());
    if (val)
        WMsgBox::information(tr("Report Success!"));
    else
        WMsgBox::information(tr("Report Failed!"));
}

void CardLostPage::updateLanguage()
{
    //update language in this page
    mainTitle->setText(tr("Credit Card Loss Report"));
    label1->setText(tr("Card number"));
    reportBtn->setText(tr("REPORT"));
}

UserInfoPage::UserInfoPage(QWidget *parent) : WPage(parent)
{
    //components new
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

    //set object name
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

    //set disable attributes
    edit1->setEnabled(false);
    edit2->setEnabled(false);
    edit3->setEnabled(false);
    edit4->setEnabled(false);
    edit5->setEnabled(false);
    edit6->setEnabled(false);
    edit7->setEnabled(false);

    //set position and size
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

    //set info
    QVector<QString> info = WUIManip::userInfo();
    edit1->setText(info[0]);
    edit2->setText(info[1]);
    edit3->setText(info[2]);
    edit4->setText(info[3]);
    edit5->setText(info[4]);
    edit6->setText(info[5]);
    edit7->setText(info[6]);
}

void UserInfoPage::updateLanguage()
{
    //update language in this page
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
    //components new
    mainTitle->setText(tr("Change Password"));
    label1 = new QLabel(tr("Original password"), this);
    label2 = new QLabel(tr("New password"), this);
    label3 = new QLabel(tr("Confirm password"), this);
    edit1 = new QLineEdit(this);
    edit2 = new QLineEdit(this);
    edit3 = new QLineEdit(this);
    confirmBtn = new QPushButton(tr("CONFIRM"), this);

    //set object name
    label1->setObjectName("CCPLabel1");
    label2->setObjectName("CCPLabel2");
    label3->setObjectName("CCPLabel3");
    edit1->setObjectName("CCPEdit1");
    edit2->setObjectName("CCPEdit2");
    edit3->setObjectName("CCPEdit3");
    confirmBtn->setObjectName("CCPConfirmBtn");

    //set position and size
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 200, 24));
    label2->setGeometry(QRect(24, 140, 200, 24));
    label3->setGeometry(QRect(24, 188, 200, 24));
    edit1->setGeometry(QRect(288, 88, 400, 32));
    edit2->setGeometry(QRect(288, 136, 400, 32));
    edit3->setGeometry(QRect(288, 184, 400, 32));
    confirmBtn->setGeometry(QRect(584, 240, 108, 36));

    edit1->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    edit2->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    edit3->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    connect(confirmBtn, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void ChangePwPage::confirm()
{
    if (edit2->text() != edit3->text())
    {
        WMsgBox::information(tr("New Password Inconsistent!"));
        return;
    }
    QString encrypted1, encrypted2;
    QByteArray bin1, bin2;
    bin1 = QCryptographicHash::hash(edit1->text().toLatin1(), QCryptographicHash::Sha3_256);
    bin2 = QCryptographicHash::hash(edit2->text().toLatin1(), QCryptographicHash::Sha3_256);
    encrypted1.append(bin1.toHex());
    encrypted2.append(bin2.toHex());
    bool val = WUIManip::changePwd(encrypted1, encrypted2);
    if (val)
    {
        WMsgBox::information(tr("Action Success!"));
        return;
    }
    else
    {
        WMsgBox::information(tr("Action Failed!"));
        return;
    }
}

void ChangePwPage::updateLanguage()
{
    //update language in this page
    mainTitle->setText(tr("Change Password"));
    label1->setText(tr("Original password"));
    label2->setText(tr("New password"));
    label3->setText(tr("Confirm password"));
    confirmBtn->setText(tr("CONFIRM"));
}

SysMsgPage::SysMsgPage(QWidget *parent) : WPage(parent)
{
    //components new
    bgLabel = new QLabel(this);
    mainTitle->setText(tr("System Message"));
    table = new QTableWidget(this);
    bgLabel->setObjectName("CSMbg");
    table->setObjectName("CSMTable");

    //set position and size
    bgLabel->setGeometry(QRect(0, 0, 751, 566));
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    table->setGeometry(QRect(24, 72, 708, 480));
}

void SysMsgPage::setSysMsg()
{
    QVector<QString> msg = WUIManip::getSysMsg();
    table->clear();
    table->setColumnCount(2);
    table->setRowCount(msg.size() / 2);

    QStringList headers;
    headers << tr("Message Time")
            << tr("Content");
    table->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < msg.size() / 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            table->setItem(i, j, new QTableWidgetItem(msg[2 * i + j]));
            table->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }

    WDelegate *CSMDele = new WDelegate();
    table->setItemDelegate(CSMDele);

    table->verticalHeader()->hide();
    table->horizontalHeader()->setStretchLastSection(true);
    table->setShowGrid(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->setHighlightSections(false);
    table->horizontalHeader()->resizeSection(0, 172);
    table->verticalHeader()->setDefaultSectionSize(48);
}

void SysMsgPage::updateLanguage()
{
    //update language in this page
    mainTitle->setText(tr("System Message"));

    QStringList headers;
    headers << tr("Message Time")
            << tr("Content");
    table->setHorizontalHeaderLabels(headers);
}

AboutPage::AboutPage(QWidget *parent) : WPage(parent)
{
    //components new
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

    //set object name and attribute
    label1->setEnabled(false);
    label1->setObjectName("CALabel1");

    //set position and size
    mainTitle->setGeometry(QRect(24, 6, 708, 60));
    label1->setGeometry(QRect(24, 92, 708, 200));
}

void AboutPage::updateLanguage()
{
    //update language in this page
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

WelcomePage::WelcomePage(QWidget *parent) : WPage(parent)
{
    //components new
    mainTitle->setText(tr("Welcome"));
    label1 = new QTextEdit(this);
    label2 = new QTextEdit(this);
    label1->setText(tr("Click on the left navigation bar to choose function."));
    label2->setText(tr("Click on the two top right buttons for user and setting fuctions."));

    //set object name and attribute
    label1->setEnabled(false);
    label2->setEnabled(false);
    label1->setObjectName("CWLabel1");
    label2->setObjectName("CWLabel2");

    //set alignment
    mainTitle->setAlignment(Qt::AlignCenter);
    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);

    //set position and sizelabel2->setAlignment(Qt::AlignHCenter);
    mainTitle->setGeometry(QRect(124, 180, 508, 60));
    label1->setGeometry(QRect(124, 276, 508, 200));
    label2->setGeometry(QRect(74, 302, 608, 200));
}

void WelcomePage::updateLanguage()
{
    //update language in this page
    mainTitle->setText(tr("Welcome"));
    label1->setText(tr("Click on the left navigation bar to choose function."));
    label2->setText(tr("Click on the two top right buttons for user and setting fuctions."));
    mainTitle->setAlignment(Qt::AlignCenter);
    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);
}
