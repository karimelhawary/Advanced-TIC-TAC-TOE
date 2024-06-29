#include "aiwindow.h"
#include "ui_aiwindow.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "chooseaiwindow.h"
#include "aiwindow.h"
#include "ui_chooseaiwindow.h"
#include <QTimer>
#include <algorithm>

MainWindow *main2 ;
int win_1;
int lose_1;
int draw_1;
int win_2;
int lose_2;
int draw_2;
int moves_player[5]={-1,-1,-1,-1,-1};
int moves_Ai[4]={-1,-1,-1,-1};
int aiMoveIndex = 0;
qint64 game_id_selected_2;
QString username11;
QString username22="Ai";
QString username_winnerr;
QString currentPlayerSymbol_1 = "X";
QString playersympol = "X";
QString aisympol = "O";
//char PlayerScore = 0;
//char AIScore = 0;
bool playAgain_1 = false;
bool easymode = false;
bool mediummode = false;
bool hardmode = false;
bool tiee = false;
const int INF = 1000;
const int MAX_DEPTH = 9;

AIWindow::AIWindow(QWidget *parent,const QString& username_ai, const QString& email_ai)
    : QDialog(parent)
    , ui(new Ui::AIWindow)
    , m_username_ai(username_ai)
    , m_email_ai(email_ai)
{
    ui->setupUi(this);
    ui->u->setText(m_username_ai);

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
   // ui->playerscore->setFont(boldFont);
    //ui->AIscore->setFont(boldFont);
    ui->AIgameStatus->setVisible(false);
    ui->playerturn_1->setText("It's Player Turn");
    ui->u->setText((m_username_ai==" ") ? "Player (X)":m_username_ai+" (X)");
    ui->u->setFont(boldFont);
    ui->u->setAlignment(Qt::AlignCenter);
    ui->playerturn_1->setText("Your Turn");

    connect(ui->btn10, &QPushButton::clicked, this, &AIWindow::handleButtonClick);
    connect(ui->btn11, &QPushButton::clicked, this, &AIWindow::handleButtonClick);
    connect(ui->btn12, &QPushButton::clicked, this, &AIWindow::handleButtonClick);
    connect(ui->btn13, &QPushButton::clicked, this, &AIWindow::handleButtonClick);
    connect(ui->btn14, &QPushButton::clicked, this, &AIWindow::handleButtonClick);
    connect(ui->btn15, &QPushButton::clicked, this, &AIWindow::handleButtonClick);
    connect(ui->btn16, &QPushButton::clicked, this, &AIWindow::handleButtonClick);
    connect(ui->btn17, &QPushButton::clicked, this, &AIWindow::handleButtonClick);
    connect(ui->btn18, &QPushButton::clicked, this, &AIWindow::handleButtonClick);
    showChooseDefficulity();
}

bool AIWindow::isGameOver(){
    if((!ui->btn10->text().isEmpty() && ui->btn10->text() == ui->btn11->text() && ui->btn10->text()==ui->btn12->text()) ||
        (!ui->btn13->text().isEmpty() && ui->btn13->text() == ui->btn14->text() && ui->btn13->text()==ui->btn15->text()) ||
        (!ui->btn16->text().isEmpty() && ui->btn16->text() == ui->btn17->text() && ui->btn16->text()==ui->btn18->text()) ||
        (!ui->btn10->text().isEmpty() && ui->btn10->text() == ui->btn13->text() && ui->btn10->text()==ui->btn16->text()) ||
        (!ui->btn11->text().isEmpty() && ui->btn11->text() == ui->btn14->text() && ui->btn11->text()==ui->btn17->text()) ||
        (!ui->btn12->text().isEmpty() && ui->btn12->text() == ui->btn15->text() && ui->btn12->text()==ui->btn18->text()) ||
        (!ui->btn10->text().isEmpty() && ui->btn10->text() == ui->btn14->text() && ui->btn10->text()==ui->btn18->text()) ||
        (!ui->btn12->text().isEmpty() && ui->btn12->text() == ui->btn14->text() && ui->btn12->text()==ui->btn16->text())){
        return true;
    } else if(isfull()){
        tiee = true;
        return true;
    }
    return false;
}

void AIWindow::resetGame() {
    // Clear the text of all buttons and enable them
    QList<QPushButton *> buttons = this->findChildren<QPushButton *>();
    foreach (QPushButton *button, buttons) {
        button->setText("");
        button->setEnabled(true);
    }
    // Reset other relevant variables or UI elements
    ui->AIgameStatus->clear();
    currentPlayerSymbol_1 = "X";
    ui->playerturn_1->setText("Your Turn");
    tiee=false;

    // Reset moves arrays
    for (int i = 0; i < 5; ++i) {
        moves_player[i] = -1;
    }
    for (int i = 0; i < 4; ++i) {
        moves_Ai[i] = -1;
    }
    aiMoveIndex = 0;
}


void AIWindow::showDialog(){
    Dialog dialog(this);
    connect(&dialog, &Dialog::response, this, &AIWindow::handleResponse);
    dialog.exec();
}

void AIWindow::showChooseDefficulity(){
    ChooseAIWindow defficulity(this);
    connect(&defficulity, &ChooseAIWindow::easy_clicked, this, &AIWindow::if_easy_clicked);
    connect(&defficulity, &ChooseAIWindow::medium_clicked, this, &AIWindow::if_medium_clicked);
    connect(&defficulity, &ChooseAIWindow::hard_clicked, this, &AIWindow::if_hard_clicked);
    defficulity.exec();
}

void AIWindow::handleResponse(bool msg) {
    if (msg) {
        playAgain_1=true;
    } else {
        playAgain_1=false;
    }
}

void AIWindow::if_easy_clicked(bool easy){
    if(easy){
        easymode = true;
    } else {
        easymode = false;
    }
}

void AIWindow::if_medium_clicked(bool medium){
    if(medium){
        mediummode = true;
    } else {
        mediummode = false;
    }
}

void AIWindow::if_hard_clicked(bool hard){
    if(hard){
        hardmode = true;
    } else {
        hardmode = false;
    }
}

void AIWindow::ButtonsOff(){
    QList<QPushButton *> buttons = this->findChildren<QPushButton *>();
    foreach (QPushButton *button, buttons){
        button->setEnabled(false);
    }
}

void AIWindow::BoardCheck(){
    if (isGameOver()) {
        ButtonsOff();
        ui->AIgameStatus->setVisible(true);
        QCoreApplication::addLibraryPath("C:\\Qt\\6.7.0\\mingw_64\\plugins\\sqldrivers");
        if (QSqlDatabase::contains("qt_sql_default_connection")) {
            QSqlDatabase::database("qt_sql_default_connection").close();
            QSqlDatabase::removeDatabase("qt_sql_default_connection");
        }
        QSqlDatabase tictactoe = QSqlDatabase::addDatabase("QSQLITE");
        tictactoe.setDatabaseName("C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db");
        if (tictactoe.open()) {qDebug() << "Database is connected successfully(Ai).";}
        else{ qDebug() << "Error66: connection with database failed.";}
        username11=m_username_ai;
        if (tiee)
        {
            username_winnerr ="No Winner";
            if (tictactoe.open())
            {   QSqlQuery query1;
                query1.prepare("SELECT * FROM Players_Data where username =:username1 ");
                query1.bindValue(":username1",username11);
                if (query1.exec()&&query1.next())
                {   draw_1 = query1.value(11).toInt();
                    draw_1++;
                    QSqlQuery updateQuery1;
                    updateQuery1.prepare("UPDATE Players_Data SET  draw_number = :new_value1 WHERE username = :username1");
                    updateQuery1.bindValue(":new_value1", draw_1);
                    updateQuery1.bindValue(":username1", username11);
                    if (!updateQuery1.exec()) {qDebug() << "Error executing UPDATE query:" << updateQuery1.lastError().text();}
                    else {qDebug() << "Data58 updated successfully";}
                }
                else {qDebug() << "No21 row found for the given ID.";}
            }
            else{qDebug() << "Error254: Database don't opened .";}

            if (tictactoe.open()){
                QSqlQuery query2;
                query2.prepare("SELECT * FROM Players_Data where username =:username2 ");
                query2.bindValue(":username2",username22);
                if (query2.exec()&&query2.next())
                {  draw_2 = query2.value(11).toInt();
                   draw_2++;
                    QSqlQuery updateQuery2;
                    updateQuery2.prepare("UPDATE Players_Data SET  draw_number = :new_value2 WHERE username = :username2");
                    updateQuery2.bindValue(":new_value2", draw_2);
                    updateQuery2.bindValue(":username2", username22);
                    if (!updateQuery2.exec()) {qDebug() << "Error executing UPDATE query:" << updateQuery2.lastError().text();}
                    else {qDebug() << "Data4 updated successfully";}
                }
                else {qDebug() << "No12 row found for the given ID.";}
            }
            else{qDebug() << "Error351: Database don't opened .";}
            ui->AIgameStatus->setText("It's a Tie!");
            tiee = false;
        }
        else if (currentPlayerSymbol_1 == playersympol) {
            username_winnerr= username11;
            if (tictactoe.open())
            {   QSqlQuery query4;
                query4.prepare("SELECT * FROM Players_Data where username =:username1 ");
                query4.bindValue(":username1",username11);
                if (query4.exec()&&query4.next())
                {win_1  = query4.value(9).toInt();
                 win_1++;
                    QSqlQuery updateQuery4;
                    updateQuery4.prepare("UPDATE Players_Data SET  win_number = :new_value1 WHERE username = :username1");
                    updateQuery4.bindValue(":new_value1", win_1);
                    updateQuery4.bindValue(":username1", username11);
                    if (!updateQuery4.exec()) {qDebug() << "Error executing UPDATE query:" << updateQuery4.lastError().text();}
                    else {qDebug() << "Data225 updated successfully";}
                    }
                else {qDebug() << "No341 row found for the given ID.";}
            }
            else{qDebug() << "Error155: Database don't opened .";}

            if (tictactoe.open()){
                QSqlQuery query5;
                query5.prepare("SELECT * FROM Players_Data where username =:username2 ");
                query5.bindValue(":username2",username22);
                if (query5.exec()&&query5.next())
                {   lose_2 = query5.value(10).toInt();
                    lose_2++;
                    QSqlQuery updateQuery5;
                    updateQuery5.prepare("UPDATE Players_Data SET  lose_number = :new_value2 WHERE username = :username2");
                    updateQuery5.bindValue(":new_value2", lose_2);
                    updateQuery5.bindValue(":username2", username22);
                    if (!updateQuery5.exec()) {qDebug() << "Error executing UPDATE query:" << updateQuery5.lastError().text();}
                    else {qDebug() << "Data241 updated successfully";}
                }
                else {qDebug() << "No215 row found for the given ID.";}
            }
            else{qDebug() << "Error1154: Database don't opened .";}
            ui->AIgameStatus->setText("You Won!");
        }
        else {
            username_winnerr= username22;
            if (tictactoe.open())
            {   QSqlQuery query7;
                query7.prepare("SELECT * FROM Players_Data where username =:username1 ");
                query7.bindValue(":username1",username11);
                if (query7.exec()&&query7.next())
                {
                    lose_1  = query7.value(10).toInt();
                    lose_1++;
                    QSqlQuery updateQuery7;
                    updateQuery7.prepare("UPDATE Players_Data SET  lose_number = :new_value1 WHERE username = :username1");
                    updateQuery7.bindValue(":new_value1", lose_1);
                    updateQuery7.bindValue(":username1", username11);
                    if (!updateQuery7.exec()) {qDebug() << "Error executing UPDATE query:" << updateQuery7.lastError().text();}
                    else {//qDebug() << "Data215 updated successfully";
                    }
                }
                else {//qDebug() << "No610 row found for the given ID.";
                }
            }
            else{//qDebug() << "Error21: Database don't opened .";
            }

            if (tictactoe.open()){
                QSqlQuery query8;
                query8.prepare("SELECT * FROM Players_Data where username =:username2 ");
                query8.bindValue(":username2",username22);
                if (query8.exec()&&query8.next())
                {   win_2 = query8.value(9).toInt();
                    win_2++;
                    QSqlQuery updateQuery8;
                    updateQuery8.prepare("UPDATE Players_Data SET  win_number = :new_value2 WHERE username = :username2");
                    updateQuery8.bindValue(":new_value2", win_2);
                    updateQuery8.bindValue(":username2", username22);
                    if (!updateQuery8.exec()) {//qDebug() << "Error executing UPDATE query:" << updateQuery8.lastError().text();
                    }
                    else {//qDebug() << "Data212 updated successfully";
                    }
                }
                else {//qDebug() << "No450 row found for the given ID.";
                    }
            }
            else{//qDebug() << "Error212: Database don't opened .";
                }
            ui->AIgameStatus->setText("Ai Won!");
        }

           // QTimer::singleShot(700, this);
            QSqlQuery query2;
            query2.prepare("INSERT INTO Games_data (username1,username2, username_winner) VALUES (:username1, :username2, :username_winner)");
            query2.bindValue(":username1", username11);
            query2.bindValue(":username2", username22);
            query2.bindValue(":username_winner",username_winnerr);
            if (query2.exec())
            {
                qDebug() << "Data Ai is inserted";
                game_id_selected_2 = query2.lastInsertId().toLongLong();
                qDebug() << "Game ID is : "<< game_id_selected_2;
                QSqlQuery query1;
                query1.prepare("INSERT INTO Moves (game_id,move_1,move_2,move_3,move_4,move_5,move_6,move_7,move_8,move_9) VALUES (:game_id, :move_1, :move_2, :move_3, :move_4, :move_5, :move_6, :move_7, :move_8, :move_9)");
                query1.bindValue(":game_id", game_id_selected_2);
                query1.bindValue(":move_1", moves_player[0]);
                query1.bindValue(":move_2", moves_Ai[0]);
                query1.bindValue(":move_3", moves_player[1]);
                query1.bindValue(":move_4", moves_Ai[1]);
                query1.bindValue(":move_5", moves_player[2]);
                query1.bindValue(":move_6", moves_Ai[2]);
                query1.bindValue(":move_7", moves_player[3]);
                query1.bindValue(":move_8", moves_Ai[3]);
                query1.bindValue(":move_9", moves_player[4]);
                if (query1.exec())
                {
                    qDebug() << "Data for Ai is ready to replied";
                }
                else
                {qDebug() << "Failed to insert data:" << query1.lastError().text();}
            }
            else
            {qDebug() << "Failed to insert data:" << query2.lastError().text();}
             for(int i = 0;i<5;i++){
                qDebug()<<"move for player "<<i+1<<"is"<< moves_player[i];
             }
             for(int j= 0;j<4;j++){
                qDebug()<<"move for Ai "<<j+1<<"is"<< moves_Ai[j];
             }
             for (int i = 0; i < 5; ++i) {
                moves_player[i] = -1;
             }
             for (int j = 0; j < 4; ++j) {
                moves_Ai[j] = -1;
             }

            QTimer::singleShot(700, this, [this](){
                showDialog();
                if (playAgain_1) {
                    resetGame();
                } else {
                    resetGame();
                    openMainWindow(m_username_ai);
                    close();
                }
            });
         tictactoe.close();
        //}
    }
}


void AIWindow::Easymove() {
    QList<QPushButton*> emptyButtons;
    for (int i = 10; i <= 18; ++i) {
        QPushButton *button = findChild<QPushButton*>("btn" + QString::number(i));
        if (button && button->text().isEmpty()) {
            emptyButtons.append(button);
        }
    }
    if (!emptyButtons.isEmpty()) {
        srand(time(nullptr)); // Seed for random number generator
        int randomIndex = rand() % emptyButtons.size();
        QPushButton *randomButton = emptyButtons[randomIndex];
        randomButton->setText(currentPlayerSymbol_1);
        randomButton->setEnabled(false);

        // Store AI move
        int btn_index = randomButton->objectName().mid(3).toInt() - 10;
        if (aiMoveIndex < 4) {
            moves_Ai[aiMoveIndex++] = btn_index;
        }
    }
}

void AIWindow::Mediummove() {
    // Check if AI can win in the next move
    for (int z = 10; z <= 18; ++z) {
        QPushButton *button = findChild<QPushButton*>("btn" + QString::number(z));
        if (button && button->text().isEmpty()) {
            button->setText(currentPlayerSymbol_1);
            if (isGameOver()) {
                button->setEnabled(false);
                int btn_index = z - 10;
                if (aiMoveIndex < 4) {
                    moves_Ai[aiMoveIndex++] = btn_index;
                }
                tiee = false;
                return;
            }
            button->setText("");
        }
    }
    currentPlayerSymbol_1 = (currentPlayerSymbol_1 == "X") ? "O" : "X";
    for (int z = 10; z <= 18; ++z) {
        QPushButton *button = findChild<QPushButton*>("btn" + QString::number(z));
        if (button && button->text().isEmpty()) {
            button->setText(currentPlayerSymbol_1);
            if (isGameOver()) {
                currentPlayerSymbol_1 = (currentPlayerSymbol_1 == "X") ? "O" : "X";
                button->setText(currentPlayerSymbol_1);
                button->setEnabled(false);
                int btn_index = z - 10;
                if (aiMoveIndex < 4) {
                    moves_Ai[aiMoveIndex++] = btn_index;
                }
                tiee = false;
                return;
            }
            button->setText("");
        }
    }
    currentPlayerSymbol_1 = (currentPlayerSymbol_1 == "X") ? "O" : "X";
    Easymove();
}

bool AIWindow::checkwin(QString sympol) {
    if ((ui->btn10->text() == sympol && ui->btn11->text() == sympol && ui->btn12->text() == sympol) ||
        (ui->btn13->text() == sympol && ui->btn14->text() == sympol && ui->btn15->text() == sympol) ||
        (ui->btn16->text() == sympol && ui->btn17->text() == sympol && ui->btn18->text() == sympol) ||
        (ui->btn10->text() == sympol && ui->btn13->text() == sympol && ui->btn16->text() == sympol) ||
        (ui->btn11->text() == sympol && ui->btn14->text() == sympol && ui->btn17->text() == sympol) ||
        (ui->btn12->text() == sympol && ui->btn15->text() == sympol && ui->btn18->text() == sympol) ||
        (ui->btn10->text() == sympol && ui->btn14->text() == sympol && ui->btn18->text() == sympol) ||
        (ui->btn12->text() == sympol && ui->btn14->text() == sympol && ui->btn16->text() == sympol)) {
        return true;
    } else return false;
}

bool AIWindow::isfull(){
    if(!ui->btn10->text().isEmpty() && !ui->btn11->text().isEmpty() && !ui->btn12->text().isEmpty() && !ui->btn13->text().isEmpty()
        && !ui->btn14->text().isEmpty() && !ui->btn15->text().isEmpty() && !ui->btn16->text().isEmpty() && !ui->btn17->text().isEmpty()
        && !ui->btn18->text().isEmpty()) return true;
    else return false;
}

int AIWindow::MiniMax(bool maximizingPlayer, int depth, int alpha, int beta) {
    if (checkwin(playersympol)) return -10;
    if (checkwin(aisympol)) return 10;
    if (isfull()) return 0;

    if (maximizingPlayer) {
        int MaxScore = -INF;
        for (int i = 10; i <= 18; ++i) {
            QPushButton *button = findChild<QPushButton *>("btn" + QString::number(i));
            if (button->text().isEmpty()) {
                button->setText(aisympol);
                int score = MiniMax(false, depth + 1, alpha, beta);
                button->setText("");
                MaxScore = std::max(MaxScore, score);
                alpha = std::max(alpha, score);
                if (beta <= alpha) break;
            }
        }
        return MaxScore;
    } else {
        int MinScore = INF;
        for (int i = 10; i <= 18; ++i) {
            QPushButton *button = findChild<QPushButton *>("btn" + QString::number(i));
            if (button && button->text().isEmpty()) {
                button->setText(playersympol);
                int score = MiniMax(true, depth + 1, alpha, beta);
                button->setText("");
                MinScore = std::min(MinScore, score);
                beta = std::min(beta, score);
                if (beta <= alpha) break;
            }
        }
        return MinScore;
    }
}

void AIWindow::Hardmove() {
    int bestScore = -INF;
    int moveindex = -1;
    for (int i = 10; i <= 18; ++i) {
        QPushButton *button = findChild<QPushButton*>("btn" + QString::number(i));
        if (button && button->text().isEmpty()) {
            button->setText(aisympol);
            int score = MiniMax(false, 0, -INF, INF);
            button->setText("");
            if (score > bestScore) {
                bestScore = score;
                moveindex = i;
            }
        }
    }
    if (moveindex != -1) {
        QPushButton *bestMove = findChild<QPushButton *>("btn" + QString::number(moveindex));
        bestMove->setText(aisympol);
        bestMove->setEnabled(false);

        // Store AI move
        int btn_index = moveindex - 10;
        if (aiMoveIndex < 4) {
            moves_Ai[aiMoveIndex++] = btn_index;
        }
    }
}

void AIWindow::handleButtonClick() {
    currentPlayerSymbol_1 = "X";
    QPushButton *button = qobject_cast<QPushButton*>(sender()); // Get the sender button
    // Set text and disable the clicked button
    button->setText(currentPlayerSymbol_1);
    button->setEnabled(false);
    int btn_index=-1;

    if(button==ui->btn10) btn_index=0;
    else if(button==ui->btn11) btn_index=1;
    else if(button==ui->btn12) btn_index=2;
    else if(button==ui->btn13) btn_index=3;
    else if(button==ui->btn14) btn_index=4;
    else if(button==ui->btn15) btn_index=5;
    else if(button==ui->btn16) btn_index=6;
    else if(button==ui->btn17) btn_index=7;
    else if(button==ui->btn18) btn_index=8;

    for(int i = 0;i<5;i++){
        if(moves_player[i]==-1){
            moves_player[i] = btn_index;
            break;
        }
    }
    BoardCheck();
    // If the game is not over, toggle the player symbol and update the UI
    currentPlayerSymbol_1 = (currentPlayerSymbol_1 == "X") ? "O" : "X";

    ui->playerturn_1->setText("It's " + QString((currentPlayerSymbol_1 == playersympol ? "Your" : "AI")) + " Turn");
    ButtonsOff();
    if(!isGameOver()){

        if (currentPlayerSymbol_1 == "O"){
            QTimer::singleShot(700, this, [this](){
                if (easymode){
                    Easymove();
                } else if(mediummode){
                    Mediummove();
                } else if(hardmode){
                    Hardmove();
                }

                // ButtonsOff();
                BoardCheck();
                if(!isGameOver()){
                    currentPlayerSymbol_1 = (currentPlayerSymbol_1 == "X") ? "O" : "X";
                    ui->playerturn_1->setText("It's " + QString((currentPlayerSymbol_1 == playersympol ? "Your" : "AI")) + " Turn");
                }
                QTimer::singleShot(700, this, [this](){

                for (int k = 10; k <= 18; ++k) {
                    QPushButton *button = findChild<QPushButton*>("btn" + QString::number(k));
                    if (button && button->text().isEmpty()) {
                        button->setEnabled(true);
                    }


                }});
            });

        }
        ui->playerturn_1->setText("It's " + QString((currentPlayerSymbol_1 == playersympol ? "Your" : "AI")) + " Turn");
    }
}
void AIWindow::openMainWindow(const QString& username){
    main2 = new MainWindow(nullptr,username);
    main2->show();
}

AIWindow::~AIWindow()
{
    delete ui;
}
