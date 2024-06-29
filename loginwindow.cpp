#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "sessionmanager.h"
QString username;
QString password;
QString email;

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(ui->login    , SIGNAL(click()), this, SLOT(openMainWindow())) ;
    connect(ui->sign_up  , SIGNAL(click()), this, SLOT(openSignupWindow())) ;
    connect(ui->guest    , SIGNAL(click()), this, SLOT(openMainWindow())) ;
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

QString hashPasswordAtLogin(QString password){
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}


void LoginWindow::openMainWindow(const QString& username, const QString& email){
    mainwindow = new MainWindow(nullptr,username,email);
    mainwindow->show();
}

void LoginWindow::openSignupWindow(){
    signupwindow = new SignupWindow();
    signupwindow->show();
}


void LoginWindow::on_login_clicked()
{
    ui->message_2->setVisible(false);
    tictactoe = QSqlDatabase::addDatabase("QSQLITE");
    tictactoe.setDatabaseName("C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db");
    if (tictactoe.open()) {
        qDebug() << "Database is connected successfully1.";
    }
    else
    {
        qDebug() << "Error1: connection with database failed.";
    }

    if (tictactoe.open())
    {
        QSqlQuery query;
        username= ui->username_3->text();
        password= hashPasswordAtLogin(ui->password_3->text());
        // QString mail;
        query.prepare("SELECT * FROM Players_Data where username =:username and password =:password");
        query.bindValue(":username",username);
        query.bindValue(":password",password);
        if (query.exec()&&query.next())
        {
            email = query.value(2).toString();
            SessionManager::saveSession(username, email);
            openMainWindow(username,email);
            close();
        }
        else
        {
            ui->message_2->setVisible(true);
            ui->message_2->setText(" error :login not sussesful!");
        }
    }
    tictactoe.close();
}

void LoginWindow::on_guest_clicked()
{
    close();
    openMainWindow(" "," ");
}

void LoginWindow::on_sign_up_clicked()
{
    openSignupWindow();
}

void LoginWindow::connectDatabase()
{
    tictactoe = QSqlDatabase::addDatabase("QSQLITE", "loginwindow_connection");
    tictactoe.setDatabaseName("C:\\Users\\user\\OneDrive\\Desktop\\tictactoee.db");

    if (!tictactoe.open()) {
        qDebug() << "Error: connection with database failed.";
    } else {
        qDebug() << "Database is connected successfully.";
    }
}

void LoginWindow::disconnectDatabase()
{
    tictactoe.close();
    QSqlDatabase::removeDatabase("loginwindow_connection");
}

QSqlDatabase& LoginWindow::databaseInstance()
{
    static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "loginwindow_connection");
    db.setDatabaseName("C:\\Users\\user\\OneDrive\\Desktop\\tictactoee.db");
    return db;
}
