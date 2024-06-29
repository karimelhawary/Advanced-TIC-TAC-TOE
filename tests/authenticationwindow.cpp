#include "authenticationwindow.h"
#include "ui_authenticationwindow.h"
#include "sessionmanager.h"
QString user1;
QString email1;
#include <QPixmap>

AuthenticationWindow::AuthenticationWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuthenticationWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/Kareem/Desktop/Advanced Tic Tac Toe(GridMasters)/Logo.png");
    ui->label_pic->setPixmap(pix.scaled(350,350,Qt::KeepAspectRatio));
    connect(ui->Go, SIGNAL(click()), this, SLOT(openLoginWindow()));
    SessionManager::loadSession(user1,email1);
}

void AuthenticationWindow::openLoginWindow(){
    if (!user1.isEmpty() && !email1.isEmpty()) {
        mainwindow = new MainWindow(nullptr ,user1,email1);
        mainwindow->show();
        qInfo() << "This is an informational message";
    }
    else {
        loginwindow = new LoginWindow();
        loginwindow->show();
    }
}

AuthenticationWindow::~AuthenticationWindow()
{
    delete ui;
}

void AuthenticationWindow::on_Go_clicked()
{
    openLoginWindow();
    close();
}
