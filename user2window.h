#ifndef USER2WINDOW_H
#define USER2WINDOW_H
#include "multiplayerwindow.h"
#include <QMainWindow>
#include <QSet>
//A Qt library which generates a fixed size strings or numbers derived from the password I am hashing.
#include <QCryptographicHash>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QString>

namespace Ui {
class User2Window;
}

class User2Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit User2Window(QWidget *parent = nullptr,const QString& username = "");
    ~User2Window();

public slots:
    void openMultiPlayerWindow(const QString& s_username,const QString& username_2);
private slots:
    void on_login_clicked();

 private:
    MultiPlayerWindow *multiplayerwindow;

private:
    Ui::User2Window *ui;
    QSqlDatabase tictactoe;
    QString s_username;
};

#endif // USER2WINDOW_H
