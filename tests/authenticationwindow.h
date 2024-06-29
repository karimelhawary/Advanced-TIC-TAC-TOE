#ifndef AUTHENTICATIONWINDOW_H
#define AUTHENTICATIONWINDOW_H
#include <QMainWindow>
#include "loginwindow.h"
#include <QLabel>
#include "mainwindow.h"
//#include <QPainter>

namespace Ui {
class AuthenticationWindow;
}

class AuthenticationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AuthenticationWindow(QWidget *parent = nullptr);
    ~AuthenticationWindow();

public slots:
    void openLoginWindow();

private slots:

    void on_Go_clicked();
protected:
    //void paintEvent(QPaintEvent *event) override; // Add paintEvent override declaration
private:
    LoginWindow *loginwindow;
    MainWindow *mainwindow;

private:
    Ui::AuthenticationWindow *ui;
};

#endif // AUTHENTICATIONWINDOW_H
