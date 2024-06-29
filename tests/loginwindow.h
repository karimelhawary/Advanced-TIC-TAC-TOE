#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include "mainwindow.h"
#include "signupwindow.h"
//#include <QPainter>
#include <QMainWindow>
#include <QString>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    Ui::LoginWindow *ui;
    MainWindow   *mainwindow   ;
public slots:
    void openMainWindow(const QString& username, const QString& email);
    void openSignupWindow();
    void connectDatabase();
    void disconnectDatabase();
    QSqlDatabase& databaseInstance();

private slots:
    void on_login_clicked();
    void on_guest_clicked();
    void on_sign_up_clicked();
protected:
     // void paintEvent(QPaintEvent *event) override; // Add paintEvent override declaration
private:

    SignupWindow *signupwindow ;

private:

    QSqlDatabase tictactoe;
};

#endif // LOGINWINDOW_H
