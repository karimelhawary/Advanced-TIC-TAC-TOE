#include "replaygamewindow.h"
#include "ui_replaygamewindow.h"
#include<QTimer>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>

// Global variables should be avoided, consider making these member variables if possible
QString currentPlayerSymbol_replay = "X";
int moves_arr_replay[9] = {-1};
QString winner;

// Constructor
ReplayGameWindow::ReplayGameWindow(QWidget *parent, const QString& username1, const QString& username2, const int game_id_replay)
    : QDialog(parent)
    , ui(new Ui::ReplayGameWindow)
    , m_username1(username1)
    , m_username2(username2)
    , m_game_id_replay(game_id_replay)
    , m_currentMessageIndex(0)  // Initialize the current message index
{
    ui->setupUi(this);
    QList<QPushButton *> buttons = this->findChildren<QPushButton *>();
    foreach (QPushButton *button, buttons) {
        QFont font = button->font();
        font.setPointSize(14);
        button->setFont(font);
    }

    QList<QLabel *> labels = this->findChildren<QLabel *>();
    foreach (QLabel *label, labels) {
        QFont font = label->font();
        font.setPointSize(14);
        label->setFont(font);
    }

   // ui->game_id_txt->setVisible(true);
    ui->game_id_label->setText("Game ID:  "+ (QString::number(m_game_id_replay)));
    QFont boldFont;
    boldFont.setPointSize(14);
    boldFont.setBold(true);
    ui->gameStatus->setVisible(false);

    ui->player1name->setText(m_username1+" (X)");
    ui->player1name->setFont(boldFont);
    ui->player1name->setAlignment(Qt::AlignCenter);

    ui->player2name->setText(m_username2+ " (O)");
    ui->player2name->setFont(boldFont);
    ui->player2name->setAlignment(Qt::AlignCenter);

    ui->playerturn->setText("It's "+m_username1+" Turn");
    ui->playerturn->setAlignment(Qt::AlignCenter);

    tictactoe = QSqlDatabase::addDatabase("QSQLITE");
    tictactoe.setDatabaseName("C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db");
    if (tictactoe.open())
    {
        qDebug() << "Database is connected successfully.";
    } else
    {
        qDebug() << "Error: connection with database failed.";
    }
    QSqlQuery query;
    qDebug() << "game_id: " << m_game_id_replay;
    query.prepare("SELECT * FROM Games_data WHERE game_id = :game_id");
    query.bindValue(":game_id", m_game_id_replay);
     if (query.exec() && query.next())
    { winner =query.value(3).toString();
         qDebug()<<"The winner is "<<winner;
    }
     else {}

    QSqlQuery query2;
    int game_id = m_game_id_replay;
    qDebug() << "game_id: " << game_id;
    query2.prepare("SELECT * FROM Moves WHERE game_id = :game_id");
    query2.bindValue(":game_id", game_id);
    if (query2.exec() && query2.next())
    {
        for(int i = 0; i < 9; i++)
        {
            moves_arr_replay[i] = query2.value(i + 1).toInt();
            qDebug() << i + 1 << " move: " << moves_arr_replay[i];
        }
    }
    else
    {
        qDebug() << "Failed to select data: " << query2.lastError().text();
    }
    tictactoe.close();

    // Initialize the QTimer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ReplayGameWindow::onTimeout);

    // Start the timer with a 2-second interval
    timer->start(1000);
}

// Destructor
ReplayGameWindow::~ReplayGameWindow()
{
    delete ui;
}

// Slot to handle the timer timeout event
void ReplayGameWindow::onTimeout()
{
    if (m_currentMessageIndex < 9 && moves_arr_replay[m_currentMessageIndex] != -1)
    {
        int move = moves_arr_replay[m_currentMessageIndex];
        QPushButton* button = nullptr;

        switch (move)
        {
        case 0: button = ui->btn1; break;
        case 1: button = ui->btn2; break;
        case 2: button = ui->btn3; break;
        case 3: button = ui->btn4; break;
        case 4: button = ui->btn5; break;
        case 5: button = ui->btn6; break;
        case 6: button = ui->btn7; break;
        case 7: button = ui->btn8; break;
        case 8: button = ui->btn9; break;
        }

        if (button)
        {
            button->setText(currentPlayerSymbol_replay);
            button->setEnabled(false);
            currentPlayerSymbol_replay = (currentPlayerSymbol_replay == "X") ? "O" : "X";
            if(currentPlayerSymbol_replay=="X") ui->playerturn->setText("It's "+m_username1+" Turn");
            else ui->playerturn->setText("It's "+m_username2+" Turn");
        }

        m_currentMessageIndex++;
    }
    else
    {
        ui->gameStatus->setVisible(true);
        if(winner=="No Winner")
        ui->gameStatus->setText("It's a Tie!");
        else
            ui->gameStatus->setText(winner+" Won!");
        currentPlayerSymbol_replay = "X";

        // Stop the timer when all messages have been displayed
        timer->stop();
    }
}
