#ifndef REPLAYGAMEWINDOW_H
#define REPLAYGAMEWINDOW_H
#include <QSet>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QDialog>
#include <QTimer>

namespace Ui {
class ReplayGameWindow;
}

class ReplayGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReplayGameWindow(QWidget *parent = nullptr,const QString& username1="",const QString& username2="",int game_id_replay=0);
    ~ReplayGameWindow();



private slots:
    void onTimeout();
private:
    Ui::ReplayGameWindow *ui;
    QString m_username1;
    QString m_username2;
    int m_game_id_replay;
    QTimer *timer;
    int m_currentMessageIndex;
    QSqlDatabase tictactoe;
};

#endif // REPLAYGAMEWINDOW_H
