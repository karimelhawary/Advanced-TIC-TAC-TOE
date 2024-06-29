#ifndef REPLAYWINDOW_H
#define REPLAYWINDOW_H
#include "multiplayerwindow.h"
#include "replaygamewindow.h"
#include <QDialog>
#include <QSet>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QDebug>

namespace Ui {
class ReplayWindow;
}

class ReplayWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReplayWindow(QWidget *parent = nullptr,const QString& username = "");
    ~ReplayWindow();
public slots:
    void openReplayGameWindow(const QString& username1_replay,const QString& username2_replay,const int game_id_replay);

private slots:
    void on_dialog_replay_clicked();

private:
 //   MultiPlayerWindow *multiwindow;

private:
    Ui::ReplayWindow *ui;
    QString m_username_replay;
    QSqlDatabase tictactoe;
    ReplayGameWindow *replaygamewindow;

};

#endif // REPLAYWINDOW_H
