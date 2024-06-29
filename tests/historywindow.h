#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H
#include <QDebug>
#include <QMainWindow>
#include <QSet>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql>
#include <replaywindow.h>
namespace Ui {
class HistoryWindow;
}

class HistoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase tictactoe;
    explicit HistoryWindow(QWidget *parent = nullptr,
                           const QString &username_history = "",
                           const QString &email_history = "");
    ~HistoryWindow();

public slots:
    void openReplayWindow(const QString &username);
    void openMainWindow(const QString &username);

private slots:
    void on_back_clicked();
    void on_Replay_clicked();

private:
    Ui::HistoryWindow *ui;
    QString m_username_history;
    QString m_email_history;
    ReplayWindow *replaywindow;
};

#endif // HISTORYWINDOW_H
