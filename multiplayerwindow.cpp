#include "multiplayerwindow.h"
#include "ui_multiplayerwindow.h"
#include "dialog.h"
#include "mainwindow.h"
#include "ui_dialog.h"
#include <QTimer>

int win_number_1;
int lose_number_1;
int draw_number_1;
int win_number_2;
int lose_number_2;
int draw_number_2;
QString username1;
QString username2;
int moves_arr[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1};
qint64 game_id_selected;
MainWindow *mainwindow;


MultiPlayerWindow::MultiPlayerWindow(QWidget *parent,const QString& s_username,const QString& username_2)
    : QDialog(parent),
    ui(new Ui::MultiPlayerWindow)
    , m_username_multiplayer(s_username)
    , m_username_2(username_2)
    , currentPlayerSymbol("X")
    , tie(false)

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

    QFont boldFont;
    boldFont.setPointSize(14);
    boldFont.setBold(true);
    ui->gameStatus->setVisible(false);

    ui->player1name->setText((m_username_multiplayer==" ") ? "Player 1 (X)":m_username_multiplayer+" (X)");
    ui->player1name->setFont(boldFont);
    ui->player1name->setAlignment(Qt::AlignCenter);
    ui->player2name->setText((m_username_multiplayer==" ") ? "Player 2 (O)":m_username_2+" (O)");
    ui->player2name->setFont(boldFont);
    ui->player2name->setAlignment(Qt::AlignCenter);
    ui->playerturn->setText((m_username_multiplayer==" ") ? "It's Player 1 Turn":"It's "+m_username_multiplayer+"'s Turn");
    ui->playerturn->setAlignment(Qt::AlignCenter);

    connect(ui->btn1, &QPushButton::clicked, this, &MultiPlayerWindow::handleButtonClick);
    connect(ui->btn2, &QPushButton::clicked, this, &MultiPlayerWindow::handleButtonClick);
    connect(ui->btn3, &QPushButton::clicked, this, &MultiPlayerWindow::handleButtonClick);
    connect(ui->btn4, &QPushButton::clicked, this, &MultiPlayerWindow::handleButtonClick);
    connect(ui->btn5, &QPushButton::clicked, this, &MultiPlayerWindow::handleButtonClick);
    connect(ui->btn6, &QPushButton::clicked, this, &MultiPlayerWindow::handleButtonClick);
    connect(ui->btn7, &QPushButton::clicked, this, &MultiPlayerWindow::handleButtonClick);
    connect(ui->btn8, &QPushButton::clicked, this, &MultiPlayerWindow::handleButtonClick);
    connect(ui->btn9, &QPushButton::clicked, this, &MultiPlayerWindow::handleButtonClick);

}

//QString currentPlayerSymbol = "X";
char Player1Score = 0;
char Player2Score = 0;
bool playAgain = false;
//bool tie = false;

bool MultiPlayerWindow::isGameOver(){
    if(!ui->btn1->text().isEmpty() && ui->btn1->text() == ui->btn2->text() && ui->btn1->text()==ui->btn3->text())
        return true;
    if(!ui->btn4->text().isEmpty() && ui->btn4->text() ==ui->btn5->text() && ui->btn4->text()==ui->btn6->text())
        return true;
    if(!ui->btn7->text().isEmpty() && ui->btn7->text() ==ui->btn8->text() && ui->btn7->text()==ui->btn9->text())
        return true;
    if(!ui->btn1->text().isEmpty() && ui->btn1->text() ==ui->btn4->text() && ui->btn1->text()==ui->btn7->text())
        return true;
    if(!ui->btn2->text().isEmpty() && ui->btn2->text() ==ui->btn5->text() && ui->btn2->text()==ui->btn8->text())
        return true;
    if(!ui->btn3->text().isEmpty() && ui->btn3->text() ==ui->btn6->text() && ui->btn3->text()==ui->btn9->text())
        return true;
    if(!ui->btn1->text().isEmpty() && ui->btn1->text() ==ui->btn5->text() && ui->btn1->text()==ui->btn9->text())
        return true;
    if(!ui->btn3->text().isEmpty() && ui->btn3->text() ==ui->btn5->text() && ui->btn3->text()==ui->btn7->text())
        return true;
    if(!ui->btn1->text().isEmpty() && !ui->btn2->text().isEmpty() && !ui->btn3->text().isEmpty() && !ui->btn4->text().isEmpty()
        && !ui->btn5->text().isEmpty() && !ui->btn6->text().isEmpty() && !ui->btn7->text().isEmpty() && !ui->btn8->text().isEmpty()
        && !ui->btn9->text().isEmpty()){
        tie = true;
        return true;
    }
    return false;
}

void MultiPlayerWindow::resetGame() {
    // Clear the text of all buttons and enable them
    QList<QPushButton *> buttons = this->findChildren<QPushButton *>();
    foreach (QPushButton *button, buttons) {
        button->setText("");
        button->setEnabled(true);
    }

    // Reset other relevant variables or UI elements
    ui->gameStatus->clear();
    currentPlayerSymbol = "X";
    ui->playerturn->setText((m_username_multiplayer==" ") ? "It's Player 1 Turn":"It's "+m_username_multiplayer+"'s Turn");

}

void MultiPlayerWindow::showDialog(){
    Dialog dialog(this);
    connect(&dialog, &Dialog::response, this, &MultiPlayerWindow::handleResponse);
    dialog.exec();
}
void MultiPlayerWindow::handleResponse(bool msg) {
    if (msg) {
        playAgain=true;
    } else {
        playAgain=false;
    }
}

void MultiPlayerWindow::ButtonsOff(){
    ui->btn1->setEnabled(false);
    ui->btn2->setEnabled(false);
    ui->btn3->setEnabled(false);
    ui->btn4->setEnabled(false);
    ui->btn5->setEnabled(false);
    ui->btn6->setEnabled(false);
    ui->btn7->setEnabled(false);
    ui->btn8->setEnabled(false);
    ui->btn9->setEnabled(false);
}

void MultiPlayerWindow::handleButtonClick() {
    QPushButton *button = qobject_cast<QPushButton*>(sender()); // Get the sender button
    // Set text and disable the clicked button
    button->setText(currentPlayerSymbol);
    button->setEnabled(false);
    int btn_index=-1;

    if(button==ui->btn1) btn_index=0;
    else if(button==ui->btn2) btn_index=1;
    else if(button==ui->btn3) btn_index=2;
    else if(button==ui->btn4) btn_index=3;
    else if(button==ui->btn5) btn_index=4;
    else if(button==ui->btn6) btn_index=5;
    else if(button==ui->btn7) btn_index=6;
    else if(button==ui->btn8) btn_index=7;
    else if(button==ui->btn9) btn_index=8;

    for(int i = 0;i<9;i++){
        if(moves_arr[i]==-1){
            moves_arr[i] = btn_index;
            break;
        }
    }

    if (isGameOver())
    {
        QCoreApplication::addLibraryPath("C:\\Qt\\6.7.0\\mingw_64\\plugins\\sqldrivers");
        if (QSqlDatabase::contains("qt_sql_default_connection")) {
            QSqlDatabase::database("qt_sql_default_connection").close();
            QSqlDatabase::removeDatabase("qt_sql_default_connection");
        }
        QSqlDatabase tictactoe= QSqlDatabase::addDatabase("QSQLITE");
        tictactoe.setDatabaseName("C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db");
        ButtonsOff();
        ui->gameStatus->setVisible(true);
        if (tie) {
            if (tictactoe.open())
            {   QSqlQuery query1;
                username1=m_username_multiplayer;
                query1.prepare("SELECT * FROM Players_Data where username =:username1 ");
                query1.bindValue(":username1",username1);
                if (query1.exec()&&query1.next())
                {   draw_number_1 = query1.value(11).toInt();
                    draw_number_1++;
                    QSqlQuery updateQuery1;
                    updateQuery1.prepare("UPDATE Players_Data SET  draw_number = :new_value1 WHERE username = :username1");
                    updateQuery1.bindValue(":new_value1", draw_number_1);
                    updateQuery1.bindValue(":username1", username1);
                    if (!updateQuery1.exec()) {qDebug() << "Error executing UPDATE query:" << updateQuery1.lastError().text();}
                    else {qDebug() << "Data1 updated successfully";}
                } else {qDebug() << "No row found for the given ID.";}
            }else{qDebug() << "Error: Database don't opened .";}

            if (tictactoe.open()){
                QSqlQuery query2;
                username2=m_username_2;
                query2.prepare("SELECT * FROM Players_Data where username =:username2 ");
                query2.bindValue(":username2",username2);
                if (query2.exec()&&query2.next())
                {   draw_number_2 = query2.value(11).toInt();
                    draw_number_2++;
                    QSqlQuery updateQuery2;
                    updateQuery2.prepare("UPDATE Players_Data SET  draw_number = :new_value2 WHERE username = :username2");
                    updateQuery2.bindValue(":new_value2", draw_number_2);
                    updateQuery2.bindValue(":username2", username2);
                    if (!updateQuery2.exec()) {qDebug() << "Error executing UPDATE query:" << updateQuery2.lastError().text();}
                    else {qDebug() << "Data2 updated successfully";}
                }
                else {qDebug() << "No row found for the given ID.";}
            }
            else{qDebug() << "Error: Database don't opened .";}

            username_winner ="No Winner";

            ui->gameStatus->setText("It's a Tie!");
            tie = false;
        } else if (currentPlayerSymbol == "X") {
            if (tictactoe.open())
            {   QSqlQuery query1;
                username1=m_username_multiplayer;
                query1.prepare("SELECT * FROM Players_Data where username =:username1 ");
                query1.bindValue(":username1",username1);
                if (query1.exec()&&query1.next())
                {
                    win_number_1  = query1.value(9).toInt();
                    win_number_1++;
                    QSqlQuery updateQuery1;
                    updateQuery1.prepare("UPDATE Players_Data SET  win_number = :new_value1 WHERE username = :username1");
                    updateQuery1.bindValue(":new_value1", win_number_1);
                    updateQuery1.bindValue(":username1", username1);
                    if (!updateQuery1.exec()) {qDebug() << "Error executing UPDATE query:" << updateQuery1.lastError().text();}
                    else {qDebug() << "Data3 updated successfully";}
                }else {qDebug() << "No row found for the given ID.";}
            }else{qDebug() << "Error: Database don't opened .";}

            if (tictactoe.open()){
                QSqlQuery query2;
                username2=m_username_2;
                query2.prepare("SELECT * FROM Players_Data where username =:username2 ");
                query2.bindValue(":username2",username2);
                if (query2.exec()&&query2.next())
                {   lose_number_2 = query2.value(10).toInt();
                    lose_number_2++;
                    QSqlQuery updateQuery2;
                    updateQuery2.prepare("UPDATE Players_Data SET  lose_number = :new_value2 WHERE username = :username2");
                    updateQuery2.bindValue(":new_value2", lose_number_2);
                    updateQuery2.bindValue(":username2", username2);
                    if (!updateQuery2.exec()) {qDebug() << "Error executing UPDATE query:" << updateQuery2.lastError().text();}
                    else {qDebug() << "Data4 updated successfully";}
                }
                else {qDebug() << "No row found for the given ID.";}
            }
            else{qDebug() << "Error: Database don't opened .";}

            username_winner =username1;


            ui->gameStatus->setText((m_username_multiplayer==" ") ? "Player 1 Won!":m_username_multiplayer+" Won!");
        } else {
            if (tictactoe.open())
            {   QSqlQuery query1;
                username1=m_username_multiplayer;
                query1.prepare("SELECT * FROM Players_Data where username =:username1 ");
                query1.bindValue(":username1",username1);
                if (query1.exec()&&query1.next())
                {   lose_number_1  = query1.value(10).toInt();
                    lose_number_1++;
                    QSqlQuery updateQuery1;
                    updateQuery1.prepare("UPDATE Players_Data SET  lose_number = :new_value1 WHERE username = :username1");
                    updateQuery1.bindValue(":new_value1", lose_number_1);
                    updateQuery1.bindValue(":username1", username1);
                    if (!updateQuery1.exec()) {qDebug() << "Error executing UPDATE query:" << updateQuery1.lastError().text();}
                    else {qDebug() << "Data5 updated successfully";}
                }else {qDebug() << "No row found for the given ID.";}
            }else{qDebug() << "Error: Database don't opened .";}

            if (tictactoe.open()){
                QSqlQuery query2;
                username2=m_username_2;
                query2.prepare("SELECT * FROM Players_Data where username =:username2 ");
                query2.bindValue(":username2",username2);
                if (query2.exec()&&query2.next())
                {win_number_2 = query2.value(9).toInt();
                    if (username2 == username2)
                    {win_number_2++;
                        QSqlQuery updateQuery2;
                        updateQuery2.prepare("UPDATE Players_Data SET  win_number = :new_value2 WHERE username = :username2");
                        updateQuery2.bindValue(":new_value2", win_number_2);
                        updateQuery2.bindValue(":username2", username2);
                        if (!updateQuery2.exec()) {qDebug() << "Error executing UPDATE query:" << updateQuery2.lastError().text();}
                        else {qDebug() << "Data6 updated successfully";}
                    }
                    else {qDebug() << "Conditions not met, data not incremented.";}
                }
                else {qDebug() << "No row found for the given ID.";}
            }
            else{qDebug() << "Error: Database don't opened .";}
            username_winner=username2;
            ui->gameStatus->setText((m_username_multiplayer==" ") ? "Player 2 Won!":m_username_2+" Won!");
        }


        for(int i = 0;i<9;i++){
            qDebug()<< moves_arr[i];
        }

        QSqlQuery query3;
        query3.prepare("INSERT INTO Games_data (username1,username2, username_winner) VALUES (:username1, :username2, :username_winner)");
        query3.bindValue(":username1", username1);
        query3.bindValue(":username2", username2);
        query3.bindValue(":username_winner", username_winner);
        if (query3.exec())
        {
            qDebug() << "Data3 is inserted";
            game_id_selected = query3.lastInsertId().toLongLong();
            qDebug() << "Game ID is : "<< game_id_selected;

            QSqlQuery query1;
            query1.prepare("INSERT INTO Moves (game_id,move_1,move_2,move_3,move_4,move_5,move_6,move_7,move_8,move_9) VALUES (:game_id, :move_1, :move_2, :move_3, :move_4, :move_5, :move_6, :move_7, :move_8, :move_9)");
            query1.bindValue(":game_id", game_id_selected);
            query1.bindValue(":move_1", moves_arr[0]);
            query1.bindValue(":move_2", moves_arr[1]);
            query1.bindValue(":move_3", moves_arr[2]);
            query1.bindValue(":move_4", moves_arr[3]);
            query1.bindValue(":move_5", moves_arr[4]);
            query1.bindValue(":move_6", moves_arr[5]);
            query1.bindValue(":move_7", moves_arr[6]);
            query1.bindValue(":move_8", moves_arr[7]);
            query1.bindValue(":move_9", moves_arr[8]);
            if (query1.exec())
            {
                qDebug() << "Data is ready to replied";
            }
            else
            {qDebug() << "Failed to insert data:" << query1.lastError().text();}
        }
        else
        {qDebug() << "Failed to insert data:" << query3.lastError().text();}
        tictactoe.close();
        for (int i = 0; i < 9; ++i) {
            moves_arr[i] = -1;
        }
        showDialog();
        if (playAgain) {
            resetGame();
        } else {
            openMainWindow(m_username_multiplayer);
            close();
        }
    }
    else {
        // If the game is not over, toggle the player symbol and update the UI
        currentPlayerSymbol = (currentPlayerSymbol == "X") ? "O" : "X";
        if(currentPlayerSymbol=="X"){
            ui->playerturn->setText((m_username_multiplayer==" ") ? "It's Player 1 Turn":"It's "+m_username_multiplayer+"'s Turn");
            ui->playerturn->setAlignment(Qt::AlignCenter);
        }
        else{
            ui->playerturn->setText((m_username_multiplayer==" ") ? "It's Player 2 Turn":"It's "+m_username_2+"'s Turn");
            ui->playerturn->setAlignment(Qt::AlignCenter);
        }
    }
}

void MultiPlayerWindow::openMainWindow(const QString& username){
    mainwindow = new MainWindow(nullptr,username);
    mainwindow->show();
}

QString MultiPlayerWindow::getCurrentPlayer() const
{
    QString playerName = (currentPlayerSymbol == "X") ? "Player X" : "Player O";
    return playerName;
}

MultiPlayerWindow::~MultiPlayerWindow()
{
    delete ui;
}
