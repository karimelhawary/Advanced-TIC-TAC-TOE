#include "replaywindow.h"
#include "ui_replaywindow.h"
#include "replaygamewindow.h"
int game_id=0;
QString username1_replay;
QString username2_replay;


ReplayWindow::ReplayWindow(QWidget *parent,const QString& username_replay)
    : QDialog(parent)
    , ui(new Ui::ReplayWindow)
    , m_username_replay(username_replay)

{
    ui->setupUi(this);
    connect(ui->dialog_replay, SIGNAL(click()), this, SLOT());
}

ReplayWindow::~ReplayWindow()
{
    delete ui;
}


void ReplayWindow::openReplayGameWindow(const QString& username1,const QString& username2,int game_id_replay)
{
   replaygamewindow = new ReplayGameWindow(nullptr,username1,username2,game_id_replay);
   replaygamewindow->show();
}


void ReplayWindow::on_dialog_replay_clicked()
{
    QCoreApplication::addLibraryPath("C:\\Qt\\6.7.0\\mingw_64\\plugins\\sqldrivers");
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::database("qt_sql_default_connection").close();
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }
    tictactoe = QSqlDatabase::addDatabase("QSQLITE");
    tictactoe.setDatabaseName("C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db");
    if (tictactoe.open()) {
        qDebug() << "Database is connected successfully1.";
    }
    else
    {
        qDebug() << "Error1: connection with database failed.";
    }

    if (tictactoe.open())
    {
        QSqlQuery query99;
        game_id= ui->game_id_edit->text().toInt();
        query99.prepare("SELECT * FROM Games_data where game_id =:game_id ");
        query99.bindValue(":game_id",game_id);
        if (query99.exec() && query99.next())
        {
            username1_replay = query99.value(1).toString();
            username2_replay = query99.value(2).toString();
            qDebug() << "one is : "<<username1_replay;
            qDebug() << "two is : "<<username2_replay;
            openReplayGameWindow(username1_replay,username2_replay,game_id);
            close();
        }
        else
        {
            qDebug() << "Error1: this game_id not available";
        }
    }
    tictactoe.close();
}

