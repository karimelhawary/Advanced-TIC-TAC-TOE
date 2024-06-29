#include "user2window.h"
#include "ui_user2window.h"
QString username_2;
QString password_2;
QString email_2;

User2Window::User2Window(QWidget *parent,const QString& username)
    : QMainWindow(parent)
    , ui(new Ui::User2Window)
    , s_username(username)

{
    ui->setupUi(this);
  connect(ui->login, SIGNAL(click()), this, SLOT(openMultiPlayerWindow()));
}

User2Window::~User2Window()
{
    delete ui;
}

//used to hash the password to a hexa string
QString hashPasswordATUSER2(QString password){
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}
void User2Window::openMultiPlayerWindow(const QString& s_username,const QString& username_2)
{
    multiplayerwindow = new MultiPlayerWindow(nullptr,s_username,username_2);
    multiplayerwindow->show();
}

void User2Window::on_login_clicked()
{
    ui->message_6->setVisible(false);
    tictactoe = QSqlDatabase::addDatabase("QSQLITE");
    tictactoe.setDatabaseName("C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db");
    if (tictactoe.open()) {
        qDebug() << "Database is connected successfully9.";
    }
    else
    {
        qDebug() << "Error9: connection with database failed.";
    }

    if (tictactoe.open())
    {
        QSqlQuery query4;
        username_2= ui->username_3->text();
        password_2= hashPasswordATUSER2(ui->password_3->text());
        if (username_2!=s_username)
        {
            query4.prepare("SELECT * FROM Players_Data where username =:username_2 and password =:password_2");
            query4.bindValue(":username_2",username_2);
            query4.bindValue(":password_2",password_2);
            if (query4.exec()&&query4.next())
            {
            close();
            openMultiPlayerWindow(s_username,username_2);
            }
            else
            {
            ui->message_6->setVisible(true);
            ui->message_6->setText(" error :login not sussesful!");
            }
        }
        else
        {
        ui->message_6->setVisible(true);
        ui->message_6->setText("Not valid");
        }
    }
    tictactoe.close();
}
