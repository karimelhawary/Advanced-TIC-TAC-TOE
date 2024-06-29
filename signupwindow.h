#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H
#include <QMainWindow>
#include <QSet>
#include <QSqlError>
#include <QCryptographicHash>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QDebug>
//A Qt library which generates a fixed size strings or numbers derived from the password I am hashing.

//#include <QPainter>
namespace Ui {
class SignupWindow;
}

class SignupWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();
    Ui::SignupWindow *ui;
    QSqlDatabase tictactoe;
    void on_sign_up_clicked();
private slots:


protected:
//    void paintEvent(QPaintEvent *event) override; // Add paintEvent override declaration
private:

};

#endif // SIGNUPWINDOW_H
