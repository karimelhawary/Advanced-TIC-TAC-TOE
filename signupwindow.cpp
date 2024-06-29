#include "signupwindow.h"
#include "ui_signupwindow.h"


SignupWindow::SignupWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignupWindow)
{
    ui->setupUi(this);
}

SignupWindow::~SignupWindow()
{
    delete ui;
}

//used to hash the password to a hexa string
QString hashPasswordAtSignUp(QString password){
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

void SignupWindow::on_sign_up_clicked()
{
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::database("qt_sql_default_connection").close();
    }

    tictactoe = QSqlDatabase::addDatabase("QSQLITE");
    tictactoe.setDatabaseName("C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db");
    if (tictactoe.open())
    {
        qDebug() << "Database is connected successfully2.";
    } else
    {
        qDebug() << "Error2: connection with database failed.";
    }
    QString username    = ui->username_2->text();
    QString password    = hashPasswordAtSignUp(ui->password_2->text());
    QString mail        = ui->mail_2->text();
    QString first_name  = ui->first_name_2->text();
    QString last_name   = ui->last_name_2->text();
    int     year        = ui->year_2->text().toInt();
    int     month       = ui->month_2->text().toInt();
    int     day         = ui->day_2->text().toInt();
    int win_number  =0;
    int lose_number =0;
    int draw_number =0;

    if(0<month&&month<13 )
    { if (0<day&&day<32){
            QSqlQuery checkQuery(tictactoe);
            int emailCount = checkQuery.value(0).toInt();
            if (emailCount > 0) {
                ui->message->setText("Error: Email already exists.");
                tictactoe.close();
                return;
            }

            QSqlQuery query;
            query.prepare("INSERT INTO Players_Data (username,password, mail,first_name,last_name,year,month,day,win_number,lose_number,draw_number) VALUES (:username, :password, :mail,:first_name,:last_name,:year,:month,:day,:win_number,:lose_number,:draw_number)");
            query.bindValue(":username", username);
            query.bindValue(":password", password);
            query.bindValue(":mail", mail);
            query.bindValue(":first_name", first_name);
            query.bindValue(":last_name", last_name);
            query.bindValue(":year", year);
            query.bindValue(":month", month);
            query.bindValue(":day", day);
            query.bindValue(":win_number", win_number);
            query.bindValue(":lose_number", lose_number);
            query.bindValue(":draw_number", draw_number);
            if (query.exec()){
                close();}
            else
            {
                ui->message->setText("Error: Sign Up is not sussesfully");
            }
        }
    }
    else
    {
        ui->message->setText("Invalid Month or Day");
    }

    tictactoe.close();
    QSqlDatabase::removeDatabase("qt_sql_default_connection");

}


