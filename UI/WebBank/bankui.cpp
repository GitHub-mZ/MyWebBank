#include <QMessageBox>
#include <QFile>
#include <QMenu>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QString>
#include <QGraphicsEffect>
#include <QPropertyAnimation>
#include <QSettings>

#include "bankui.h"
#include "wcurrentuser.h"
#include "wuimanip.h"
#include "wmsgbox.h"

BankUI::BankUI(QWidget *parent, int trans)
    : QWidget(parent)
{
    setTranslator(trans);
    initUI();
}

void BankUI::setTranslator(int i)
{
    isChinese = i ? true : false;
}

void BankUI::initUI()
{
    //main widget setup
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMaximumSize(1000, 750);
    this->setMinimumSize(1000, 750);
    this->setObjectName("MainWindow");
    this->setAttribute(Qt::WA_TranslucentBackground);

    //components new
    backgroundLabel = new QLabel("", this);
    navbar = new WNavbar(this);
    topbar = new WTopbar(this);
    centerStack = new WStackedWidget(this);

    //set current user info
    QString loginfo = tr("User: ");
    loginfo.append(WCurrentUser::userName);

    logInfoLabel = new QLabel(loginfo, this);
    creditLabel = new QLabel(tr("Credit to Zhu Yilin & Tian Xingyu"), this);

    //components setObjectName for QSS
    backgroundLabel->setObjectName("backgroundLabel");
    centerStack->setObjectName("centerStack");

    logInfoLabel->setObjectName("logInfoLabel");
    creditLabel->setObjectName("creditLabel");

    //components' position and size
    backgroundLabel->setGeometry(QRect(0, 0, 1000, 750));
    topbar->setGeometry(QRect(0, 0, 1000, 161));
    navbar->setGeometry(QRect(5, 0, 261, 750));
    centerStack->setGeometry(QRect(242, 152, 751, 566));

    logInfoLabel->setGeometry(QRect(10, 722, 300, 24));
    creditLabel->setGeometry(QRect(700, 724, 290, 24));

    //other settings
    creditLabel->setAlignment(Qt::AlignRight);
    openingOpacity = 0;
}

void BankUI::changeLanguage()
{
    //if language is changed
    QString t;
    QTranslator *wTranslator = new QTranslator();

    //change language settings
    isChinese ? t = ":/trans/trans/eng.qm" : t = ":/trans/trans/chn.qm";
    isChinese ? isChinese = false : isChinese = true;

    //if translator loaded, install
    if(wTranslator->load(t))
    {
        qApp->installTranslator(wTranslator);
    }

    //spread down the updating signal
    updateLanguage();

    //write current language into trans.ini
    QSettings config("config.ini", QSettings::IniFormat);
    config.setValue("TRANS", isChinese ? ":/trans/trans/chn.qm" : ":/trans/trans/eng.qm");
}

void BankUI::updateLanguage()
{
    //update the language in this widget
    QString loginfo = tr("User: ");
    loginfo.append(WCurrentUser::userName);
    logInfoLabel->setText(loginfo);
    creditLabel->setText(tr("Credit to Zhu Yilin & Tian Xingyu"));

    //update language in son widgets
    topbar->updateLanguage();
    navbar->updateLanguage();
    centerStack->updateLanguage();
}

void BankUI::changeColor()
{
    //if color is changed
    WMsgBox::color(this);
}

void BankUI::changeToBlue()
{
    //change color settings and write into color.ini
    QSettings colorConfig("config.ini", QSettings::IniFormat);
    colorConfig.setValue("QSS", ":/ui/ui_blue.qss");
    colorConfig.setValue("LOGO", ":/image/image/blue/logo.png");
    //restart the window
    closeColor();
}

void BankUI::changeToGreen()
{
    //change color settings and write into color.ini
    QSettings colorConfig("config.ini", QSettings::IniFormat);
    colorConfig.setValue("QSS", ":/ui/ui_green.qss");
    colorConfig.setValue("LOGO", ":/image/image/green/logo.png");
    //restart the window
    closeColor();
}

void BankUI::changeToOrange()
{
    //change color settings and write into color.ini
    QSettings colorConfig("config.ini", QSettings::IniFormat);
    colorConfig.setValue("QSS", ":/ui/ui_orange.qss");
    colorConfig.setValue("LOGO", ":/image/image/orange/logo.png");
    //restart the window
    closeColor();
}

void BankUI::changeToPurple()
{
    //change color settings and write into color.ini
    QSettings colorConfig("config.ini", QSettings::IniFormat);
    colorConfig.setValue("QSS", ":/ui/ui_purple.qss");
    colorConfig.setValue("LOGO", ":/image/image/purple/logo.png");
    //restart the window
    closeColor();
}

void BankUI::changeToRed()
{
    //change color settings and write into color.ini
    QSettings colorConfig("config.ini", QSettings::IniFormat);
    colorConfig.setValue("QSS", ":/ui/ui_red.qss");
    colorConfig.setValue("LOGO", ":/image/image/red/logo.png");
    //restart the window
    closeColor();
}

void BankUI::changeToYellow()
{
    //change color settings and write into color.ini
    QSettings colorConfig("config.ini", QSettings::IniFormat);
    colorConfig.setValue("QSS", ":/ui/ui_yellow.qss");
    colorConfig.setValue("LOGO", ":/image/image/yellow/logo.png");
    //restart the window
    closeColor();
}

void BankUI::mouseMoveEvent(QMouseEvent *event)
{
    //if mouse click on top or bottom bar and drag, move the window
    if (isPressed && (movePoint.ry() < 160 || movePoint.ry() > 726))
    {
        QPoint point = event->globalPos();
        move(point - movePoint);
    }
}

void BankUI::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        isPressed = true;
    movePoint = event->globalPos() - pos();
}

void BankUI::mouseReleaseEvent(QMouseEvent *event)
{
    event;
    isPressed = false;
}

//the following are the slots for buttons on navbar
void BankUI::showMyAccountPage()
{
    centerStack->myAccountPage->setTable();
    centerStack->setCurrentIndex(0);
}

void BankUI::showAccountQueryPage()
{
    centerStack->accountQueryPage->setComboBox();
    centerStack->accountQueryPage->setTable();
    centerStack->setCurrentIndex(1);
}

void BankUI::showTransferPage()
{
    centerStack->transferPage->setComboBox();
    centerStack->setCurrentIndex(2);
}

void BankUI::shouCurrentFixPage()
{
    centerStack->currentFixPage->setComboBox();
    centerStack->setCurrentIndex(3);
}

void BankUI::showPaymentPage()
{
    centerStack->paymentPage->setComboBox();
    centerStack->setCurrentIndex(4);
}

void BankUI::showAutoPayPage()
{
    centerStack->autoPayPage->setComboBox();
    centerStack->autoPayPage->setTable();
    centerStack->setCurrentIndex(5);
}

void BankUI::showCardApplyPage()
{
    centerStack->setCurrentIndex(6);
}

void BankUI::showCardActivatePage()
{
    centerStack->cardActivatePage->setComboBox();
    centerStack->setCurrentIndex(7);
}

void BankUI::showCardRepayPage()
{
    centerStack->cardRepayPage->setComboBox();
    centerStack->setCurrentIndex(8);
}

void BankUI::showCardLostPage()
{
    centerStack->cardLostPage->setComboBox();
    centerStack->setCurrentIndex(9);
}

void BankUI::showUserInfoPage()
{
    centerStack->setCurrentIndex(10);
}

void BankUI::showChangePwPage()
{
    centerStack->setCurrentIndex(11);
}

void BankUI::showSysMsgPage()
{
    centerStack->sysMsgPage->setSysMsg();
    topbar->checkMsg();
    centerStack->setCurrentIndex(12);
}

void BankUI::showAboutPage()
{
    WMsgBox::about();
}

void BankUI::showWelcomePage()
{
    centerStack->setCurrentIndex(13);
}

void BankUI::showPlotPage()
{
    centerStack->plotPage->setPlot();
    centerStack->setCurrentIndex(14);
}

void BankUI::showCurrencyPage()
{
    centerStack->setCurrentIndex(15);
    centerStack->currencyPage->setCurrency();
}

//set up the opening animation
void BankUI::openUX()
{
    // QRect pos = QApplication::desktop()->screenGeometry();
    // int height = pos.height();
    // int width = pos.width();
    // QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    // animation1->setDuration(150);
    // animation1->setStartValue(QRect((width - 400) / 2, (height - 300) / 2 + 50, 400, 300));
    // animation1->setEndValue(QRect((width - 1000) / 2, (height - 750) / 2, 1000, 750));
    // animation1->setEasingCurve(QEasingCurve::OutQuint);
    // QPropertyAnimation *animation2 = new QPropertyAnimation(this, "windowOpacity");
    // animation2->setDuration(200);
    // animation2->setStartValue(0);
    // animation2->setEndValue(1);
    // animation2->setEasingCurve(QEasingCurve::OutQuint);
    // animation1->start();
    // animation2->start();
    // topbarLabel->setGeometry(QRect(0, 0, 1000, 161));
    // menubarLabel->setGeometry(QRect(0, 0, 1000, 33));
    // navbarLabel->setGeometry(QRect(0, 0, 260, 751));

    //hide all widgets first
    navbar->setVisible(false);
    logInfoLabel->setVisible(false);
    creditLabel->setVisible(false);
    centerStack->setVisible(false);

    //topbar slip from top
    QPropertyAnimation *a1 = new QPropertyAnimation(topbar, "geometry");
    a1->setDuration(1800);
    a1->setStartValue(QRect(0, -160, 1000, 161));
    a1->setEndValue(QRect(0, 0, 1000, 161));
    a1->setEasingCurve(QEasingCurve::OutExpo);
    a1->start();

    //start navbar animation after delay
    QTimer::singleShot(600, this, SLOT(openUX2()));
}

//after topbar has animated, start navbar animation
void BankUI::openUX2()
{
    //navbar slip from left
    QPropertyAnimation *a2 = new QPropertyAnimation(navbar, "geometry");
    a2->setDuration(1500);
    a2->setStartValue(QRect(0, 0, 0, 751));
    a2->setEndValue(QRect(0, 0, 260, 751));
    a2->setEasingCurve(QEasingCurve::OutExpo);
    a2->start();
    navbar->setVisible(true);

    //start center stack animation after delay
    QTimer::singleShot(800, this, SLOT(openUX3()));
}

//after navbar animation, start center stack animation
void BankUI::openUX3()
{
    //setup the timer for opacity change
    timer = new QTimer(this);
    timer->setInterval(8);
    timer->start();
    topbar->checkMsg();

    //change opacity bit by bit
    connect(timer, SIGNAL(timeout()), this, SLOT(openUX5()));
    QTimer::singleShot(5000, timer, SLOT(stop()));
    QTimer::singleShot(20, this, SLOT(openUX4()));
}

//animation after center stack shows up
void BankUI::openUX4()
{
    //make all widgets visible
    logInfoLabel->setVisible(true);
    creditLabel->setVisible(true);
    centerStack->setVisible(true);
}

//finish the opening animation
void BankUI::openUX5()
{
    //change opacity
    QGraphicsOpacityEffect *effect1 = new QGraphicsOpacityEffect;
    logInfoLabel->setGraphicsEffect(effect1);
    effect1->setOpacity(openingOpacity);
    QGraphicsOpacityEffect *effect2 = new QGraphicsOpacityEffect;
    creditLabel->setGraphicsEffect(effect2);
    effect2->setOpacity(openingOpacity);
    QGraphicsOpacityEffect *effect3 = new QGraphicsOpacityEffect;
    centerStack->setGraphicsEffect(effect3);
    effect3->setOpacity(openingOpacity);

    //step for opacity change
    openingOpacity += 0.1;
}

//animation on closing the window
bool BankUI::closeWindow()
{
    QPoint pos = this->mapToGlobal(QPoint(0, 0));
    this->setMinimumSize(400, 300);

    //set geometry change animation
    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(165);
    animation1->setStartValue(QRect(pos.rx(), pos.ry(), 1000, 750));
    animation1->setEndValue(QRect(pos.rx() + 300, pos.ry() + 250, 400, 300));
    animation1->setEasingCurve(QEasingCurve::OutSine);

    //set opacity change animation
    QPropertyAnimation *animation2 = new QPropertyAnimation(this, "windowOpacity");
    animation2->setDuration(165);
    animation2->setStartValue(1);
    animation2->setEndValue(0);

    //start animation
    animation1->start();
    animation2->start();

    //after animation done, close the window
    WUIManip::logout();
    connect(animation2, SIGNAL(finished()), this, SLOT(close()));
    return true;
}

bool BankUI::closeColor()
{
    QPoint pos = this->mapToGlobal(QPoint(0, 0));
    this->setMinimumSize(400, 300);

    //set geometry change animation
    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(180);
    animation1->setStartValue(QRect(pos.rx(), pos.ry(), 1000, 750));
    animation1->setEndValue(QRect(pos.rx() + 300, pos.ry() + 250, 400, 300));
    animation1->setEasingCurve(QEasingCurve::OutSine);

    //set opacity change animation
    QPropertyAnimation *animation2 = new QPropertyAnimation(this, "windowOpacity");
    animation2->setDuration(160);
    animation2->setStartValue(1);
    animation2->setEndValue(0);

    //start animation
    animation1->start();
    animation2->start();

    //after animation done, close the window
    QTimer::singleShot(500, this, SLOT(restartColor()));
    return true;
}

bool BankUI::restartColor()
{
    //restart qapp to change UI theme color
    qApp->exit(3);
    return true;
}

bool BankUI::restartWindow()
{
    //restart qapp to re-login
    WUIManip::logout();
    qApp->exit(2);
    return true;
}
