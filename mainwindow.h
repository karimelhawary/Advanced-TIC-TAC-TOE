#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "aiwindow.h"
#include "historywindow.h"
#include "user2window.h"
//#include <QPainter>
#include <QSet>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,const QString& username = "", const QString& email = "");
    ~MainWindow();

public slots:
    void openAIWindow(const QString& username_ai);
    void openUser2Window(const QString& username_multiplayer);
    void openHistoryWindow(const QString& username_history, const QString& email_history);
    void openLoginWindow();

private slots:
    void on_btnAI_clicked();
    void on_btnMulti_clicked();
    void on_btnProfile_clicked();
    void on_signout_clicked();

private:
    AIWindow *aiwindow;
    HistoryWindow *history;
    User2Window *user2;
    MultiPlayerWindow *multiplayerwindow;

private:
    Ui::MainWindow *ui;
    QString m_username;
    QString m_email;
};
#endif // MAINWINDOW_H
