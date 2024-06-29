#include "historywindow.h"
#include "mainwindow.h"
#include <QStandardItemModel>
#include <QString>
#include "QModelIndexList"
#include "ui_historywindow.h"
#include <QPixmap>


int wins;
int loses;
int draws;
MainWindow *main6;

HistoryWindow::HistoryWindow(QWidget *parent,const QString &username_history,const QString &email_history)
    : QMainWindow(parent)
    , ui(new Ui::HistoryWindow)

    , m_username_history(username_history)
    , m_email_history(email_history)
{
    ui->setupUi(this);
    QPixmap pix3("C:/Users/Kareem/Desktop/Advanced Tic Tac Toe(GridMasters)/back.png");
    ui->label_pic_3->setPixmap(pix3);
    QPixmap pix9("C:/Users/Kareem/Desktop/Advanced Tic Tac Toe(GridMasters)/replay.png");
    ui->label_pic_9->setPixmap(pix9);
    connect(ui->Replay, SIGNAL(click()), this, SLOT(openReplayWindow()));
    ui->username_2->setText(m_username_history);
    ui->mail_2->setText(m_email_history);
    QCoreApplication::addLibraryPath("C:\\Qt\\6.7.0\\mingw_64\\plugins\\sqldrivers");
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::database("qt_sql_default_connection").close();
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }
    QSqlDatabase tictactoe = QSqlDatabase::addDatabase("QSQLITE");
    tictactoe.setDatabaseName("C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db");
    if (tictactoe.open()) {
        qDebug() << "Database is connected successfully3.";
    } else {
        qDebug() << "Error3: connection with database failed.";
    }
    QString username1 = m_username_history;
    QString username2 = username1;
    QSqlQuery query;
    query.prepare(
        "SELECT * FROM Games_data WHERE username1 = :username1 or username2 = :username2 ");
    query.bindValue(":username1", username1);
    query.bindValue(":username2", username2);

    QSqlQuery query2;
    query2.prepare("SELECT * FROM Players_data WHERE username = :username1 ");
    query2.bindValue(":username1", username1);
    if (query2.exec() && query2.next()) {
        wins = query2.value(9).toInt();
        loses = query2.value(10).toInt();
        draws = query2.value(11).toInt();
        ui->wins_2->setText(QString::number(wins));
        ui->loses_2->setText(QString::number(loses));
        ui->draws_2->setText(QString::number(draws));
    } else {
        qDebug() << " This username is not available";
    }

    if (query.exec()) {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(std::move(query)); // Pass query by move
        ui->tableView->setModel(model);
    } else {
        qDebug() << "Query execution failed.";
    }
}

HistoryWindow::~HistoryWindow()
{
    delete ui;
}

void HistoryWindow::openReplayWindow(const QString &username)
{
    replaywindow = new ReplayWindow(nullptr, username);
    replaywindow->show();
}

void HistoryWindow::openMainWindow(const QString &username)
{
    main6 = new MainWindow(nullptr,username);
    main6->show();
}

void HistoryWindow::on_back_clicked()
{
    close();
    openMainWindow(m_username_history);
}

void HistoryWindow::on_Replay_clicked()
{
    openReplayWindow(m_username_history);
}
