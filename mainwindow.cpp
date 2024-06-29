#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sessionmanager.h"
#include "loginwindow.h"
#include <QMessageBox>
#include <QCloseEvent>
QString username_history;
QString email_history;
QString username_first;
QString username_ai;
LoginWindow *loginwindow;
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent,const QString& username, const QString& email)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_username(username)
    , m_email(email)

{
    ui->setupUi(this);
    QPixmap pix1("C:/Users/Kareem/Desktop/Advanced Tic Tac Toe(GridMasters)/logout.png");
    ui->label_pic_1->setPixmap(pix1);
    QPixmap pix2("C:/Users/Kareem/Desktop/Advanced Tic Tac Toe(GridMasters)/user.png");
    if(m_username==" ")
        ui->label_pic_2->setVisible(false);
    else ui->label_pic_2->setPixmap(pix2);
    QPixmap pix7("C:/Users/Kareem/Desktop/Advanced Tic Tac Toe(GridMasters)/Multiplayer.png");
    ui->label_pic_7->setPixmap(pix7);
    QPixmap pix8("C:/Users/Kareem/Desktop/Advanced Tic Tac Toe(GridMasters)/AI.png");
    ui->label_pic_8->setPixmap(pix8);
    connect(ui->btnAI, SIGNAL(click()), this, SLOT(openAIWindow()));
    connect(ui->btnMulti, SIGNAL(click()), this, SLOT(openUser2Window()));
    connect(ui->btnProfile, SIGNAL(click()), this, SLOT(openHistoryWindow()));
    connect(ui->signout, SIGNAL(click()), this, SLOT(openLoginWindow()));
    if(m_username==" ") ui->btnProfile->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openUser2Window(const QString& username_first)
{

    if(m_username==" "){
        multiplayerwindow = new MultiPlayerWindow(nullptr," "," ");
        multiplayerwindow->show();
        close();
    }

    else{
        user2 = new User2Window(nullptr,username_first);
        user2->show();
    }
}

void MainWindow::openHistoryWindow(const QString& username_history, const QString& email_history)
{
    history = new HistoryWindow(nullptr,username_history,email_history);
    history->show();
}

void MainWindow::openLoginWindow()
{
    loginwindow = new LoginWindow();
    loginwindow->show();
}
void MainWindow::openAIWindow(const QString& username_ai)
{
    aiwindow = new AIWindow(nullptr,username_ai);
    aiwindow->show();
}

void MainWindow::on_btnAI_clicked()
{
    username_ai=m_username;
    close();
    openAIWindow(username_ai);
}

void MainWindow::on_btnMulti_clicked()
{
    username_first=m_username;
    close();
    openUser2Window(username_first);
}

void MainWindow::on_btnProfile_clicked()
{
    username_history=m_username;
    email_history=m_email;
    close();

    openHistoryWindow(username_history,email_history);
}

void MainWindow::on_signout_clicked()
{
    SessionManager::deleteSession();
    close();
    openLoginWindow();
}

