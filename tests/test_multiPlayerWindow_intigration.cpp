#include <QtTest/QtTest>
#include "multiplayerwindow.h"
#include "ui_multiplayerwindow.h"
#include <QSqlQuery>
#include <QSqlError>

class TestMultiPlayerWindow_int : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase_mu_int();

    void testInitialSetup_mu_int();
    void testButtonClick_mu_int();
    void testGameTie_mu_int();
    void testPlayerXWin_mu_int();
    void testPlayerOWin_mu_int();

    void testDatabaseUpdate_mu_int();
private:
    MultiPlayerWindow *multiPlayerWindow;
    Ui::MultiPlayerWindow *ui;
    void verifyDatabaseState(QSqlDatabase &db, const QString &expectedPlayer1, const QString &expectedPlayer2, const QString &expectedWinner);
};

void TestMultiPlayerWindow_int::initTestCase_mu_int()
{
    multiPlayerWindow = new MultiPlayerWindow(nullptr, "Player1", "Player2");
    ui = multiPlayerWindow->ui;
    multiPlayerWindow->show();
}



void TestMultiPlayerWindow_int::testInitialSetup_mu_int()
{
    QVERIFY(ui->player1name->text() == "Player1 (X)");
    QVERIFY(ui->player2name->text() == "Player2 (O)");
    QVERIFY(ui->playerturn->text() == "It's Player1's Turn");

    QList<QPushButton *> buttons = multiPlayerWindow->findChildren<QPushButton *>();
    foreach (QPushButton *button, buttons) {
        QVERIFY(button->text().isEmpty());
        QVERIFY(button->isEnabled());
    }

    QVERIFY(ui->gameStatus->isHidden());
}

void TestMultiPlayerWindow_int::testButtonClick_mu_int()
{
    ui->btn1->click();
    QCOMPARE(ui->btn1->text(), QString("X"));
    QVERIFY(!ui->btn1->isEnabled());
    QCOMPARE(ui->playerturn->text(), QString("It's Player2's Turn"));

    ui->btn2->click();
    QCOMPARE(ui->btn2->text(), QString("O"));
    QVERIFY(!ui->btn2->isEnabled());
    QCOMPARE(ui->playerturn->text(), QString("It's Player1's Turn"));

    ui->btn3->click();
    QCOMPARE(ui->btn3->text(), QString("X"));
    QVERIFY(!ui->btn3->isEnabled());
    QCOMPARE(ui->playerturn->text(), QString("It's Player2's Turn"));
}

void TestMultiPlayerWindow_int::testGameTie_mu_int()
{
    // Specify the path to your SQLite database file
    QString dbFilePath = "C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db";

    // Create an instance of MultiPlayerWindow
    MultiPlayerWindow *multiPlayerWindow = new MultiPlayerWindow(nullptr, "Player1", "Player2");

    // Set up QSqlDatabase with the specified database file path
    // Add a specific connection name
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "testConnection");
    db.setDatabaseName(dbFilePath);

    // Check if the database was opened successfully
    if (!db.open()) {
        qDebug() << "Error: Failed to open database:" << db.lastError().text();
        delete multiPlayerWindow;
        QFAIL("Failed to open database.");
    }

    // Simulate button clicks to force a tie game
    QTest::mouseClick(multiPlayerWindow->ui->btn1, Qt::LeftButton);
    QTest::mouseClick(multiPlayerWindow->ui->btn2, Qt::LeftButton);
    QTest::mouseClick(multiPlayerWindow->ui->btn3, Qt::LeftButton);
    QTest::mouseClick(multiPlayerWindow->ui->btn4, Qt::LeftButton);
    QTest::mouseClick(multiPlayerWindow->ui->btn5, Qt::LeftButton);
    QTest::mouseClick(multiPlayerWindow->ui->btn7, Qt::LeftButton);
    QTest::mouseClick(multiPlayerWindow->ui->btn6, Qt::LeftButton);
    QTest::mouseClick(multiPlayerWindow->ui->btn9, Qt::LeftButton);
    QTest::mouseClick(multiPlayerWindow->ui->btn8, Qt::LeftButton);

    // Ensure game is over and it's a tie
    QVERIFY2(multiPlayerWindow->isGameOver(), "Game did not detect tie condition.");

    // Check database operations for a tie game
    QSqlQuery query(db);
    query.prepare("INSERT INTO Games_data (username1, username2, username_winner) VALUES (:username1, :username2, :username_winner)");
    query.bindValue(":username1", "Player1");
    query.bindValue(":username2", "Player2");
    query.bindValue(":username_winner", "No Winner");

    QVERIFY2(query.exec(), "Failed to insert data into Games_data table.");

    // Clean up
    query.finish(); // Finish the query to release resources
    db.close(); // Close the database connection
    QSqlDatabase::removeDatabase("testConnection"); // Remove the database connection

    delete multiPlayerWindow;
}



void TestMultiPlayerWindow_int::testPlayerXWin_mu_int()
{
    // Specify the path to your SQLite database file
    QString dbFilePath = "C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db";

    // Create an instance of MultiPlayerWindow
    MultiPlayerWindow *multiPlayerWindow = new MultiPlayerWindow(nullptr, "Player1", "Player2");

    // Set up QSqlDatabase with the specified database file path
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "testConnection"); // Add a specific connection name
    db.setDatabaseName(dbFilePath);

    // Check if the database was opened successfully
    if (!db.open()) {
        qDebug() << "Error: Failed to open database:" << db.lastError().text();
        delete multiPlayerWindow;
        QFAIL("Failed to open database.");
    }

    // Simulate game where 'X' wins
    QTest::mouseClick(multiPlayerWindow->ui->btn1, Qt::LeftButton); // Player1 (X) move
    QTest::mouseClick(multiPlayerWindow->ui->btn4, Qt::LeftButton); // Player2 (O) move
    QTest::mouseClick(multiPlayerWindow->ui->btn2, Qt::LeftButton); // Player1 (X) move
    QTest::mouseClick(multiPlayerWindow->ui->btn5, Qt::LeftButton); // Player2 (O) move
    QTest::mouseClick(multiPlayerWindow->ui->btn3, Qt::LeftButton); // Player1 (X) move

    // Ensure game is over and Player1 (X) wins
    QVERIFY2(multiPlayerWindow->isGameOver(), "Game did not detect 'X' win condition.");

    // Insert into database for 'X' win
    QSqlQuery query_test(db);
    query_test.prepare("INSERT INTO Games_data (username1, username2, username_winner) VALUES (:username1, :username2, :username_winner)");
    query_test.bindValue(":username1", "Player1");
    query_test.bindValue(":username2", "Player2");
    query_test.bindValue(":username_winner", "Player1"); // 'X' wins

    QVERIFY2(query_test.exec(), "Failed to insert data into Games_data table for 'X' win.");

    // Clean up
    query_test.finish(); // Finish the query to release resources
    db.close(); // Close the database connection
    QSqlDatabase::removeDatabase("testConnection"); // Remove the database connection

    delete multiPlayerWindow; // Clean up
}


void TestMultiPlayerWindow_int::testPlayerOWin_mu_int()
{
    // Specify the path to your SQLite database file
    QString dbFilePath = "C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db";

    // Create an instance of MultiPlayerWindow
    MultiPlayerWindow *multiPlayerWindow = new MultiPlayerWindow(nullptr, "Player1", "Player2");

    // Set up QSqlDatabase with the specified database file path
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "testConnection"); // Add a specific connection name
    db.setDatabaseName(dbFilePath);

    // Check if the database was opened successfully
    if (!db.open()) {
        qDebug() << "Error: Failed to open database:" << db.lastError().text();
        delete multiPlayerWindow;
        QFAIL("Failed to open database.");
    }
    // Simulate game where 'O' wins
    QTest::mouseClick(multiPlayerWindow->ui->btn1, Qt::LeftButton); // Player1 (X) move
    QTest::mouseClick(multiPlayerWindow->ui->btn4, Qt::LeftButton); // Player2 (O) move
    QTest::mouseClick(multiPlayerWindow->ui->btn2, Qt::LeftButton); // Player1 (X) move
    QTest::mouseClick(multiPlayerWindow->ui->btn5, Qt::LeftButton); // Player2 (O) move
    QTest::mouseClick(multiPlayerWindow->ui->btn7, Qt::LeftButton); // Player1 (X) move
    QTest::mouseClick(multiPlayerWindow->ui->btn6, Qt::LeftButton); // Player2 (O) move

    // Ensure game is over and Player2 (O) wins
    QVERIFY2(multiPlayerWindow->isGameOver(), "Game did not detect 'O' win condition.");

    // Insert into database for 'O' win
    QSqlQuery query(db);
    query.prepare("INSERT INTO Games_data (username1, username2, username_winner) VALUES (:username1, :username2, :username_winner)");
    query.bindValue(":username1", "Player1");
    query.bindValue(":username2", "Player2");
    query.bindValue(":username_winner", "Player2"); // 'O' wins

    QVERIFY2(query.exec(), "Failed to insert data into Games_data table for 'O' win.");

    // Clean up
    query.finish(); // Finish the query to release resources
    db.close(); // Close the database connection
    QSqlDatabase::removeDatabase("testConnection"); // Remove the database connection

    delete multiPlayerWindow; // Clean up
}


void TestMultiPlayerWindow_int::testDatabaseUpdate_mu_int()
{
    // Specify the path to your SQLite database file
    QString dbFilePath = "C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db";

    // Create an instance of MultiPlayerWindow
    MultiPlayerWindow *multiPlayerWindow = new MultiPlayerWindow(nullptr, "Player1", "Player2");

    // Set up QSqlDatabase with the specified database file path
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "testConnection"); // Add a specific connection name
    db.setDatabaseName(dbFilePath);

    // Check if the database was opened successfully
    if (!db.open()) {
        qDebug() << "Error: Failed to open database:" << db.lastError().text();
        delete multiPlayerWindow;
        QFAIL("Failed to open database.");
    }

    // Simulate button clicks to force a Player X win
    QTest::mouseClick(multiPlayerWindow->ui->btn1, Qt::LeftButton);
    QTest::mouseClick(multiPlayerWindow->ui->btn2, Qt::LeftButton);
    QTest::mouseClick(multiPlayerWindow->ui->btn4, Qt::LeftButton);
    QTest::mouseClick(multiPlayerWindow->ui->btn5, Qt::LeftButton);
    QTest::mouseClick(multiPlayerWindow->ui->btn7, Qt::LeftButton);

    // Ensure game is over and Player X is the winner
    QVERIFY2(multiPlayerWindow->isGameOver(), "Game did not detect game over condition.");
    QCOMPARE(multiPlayerWindow->getCurrentPlayer(), "Player X"); // Assuming getCurrentPlayer() is correctly implemented

    // Update the database with the game result
    QSqlQuery query(db);
    query.prepare("INSERT INTO Games_data (username1, username2, username_winner) VALUES (:username1, :username2, :username_winner)");
    query.bindValue(":username1", "Player1");
    query.bindValue(":username2", "Player2");
    query.bindValue(":username_winner", multiPlayerWindow->getCurrentPlayer());

    // Print out the query for debugging
    qDebug() << query.lastQuery();

    // Execute the query and check for errors
    if (!query.exec()) {
        qDebug() << "Error executing INSERT query:" << query.lastError().text();
        db.close();
        QSqlDatabase::removeDatabase("testConnection");
        delete multiPlayerWindow;
        QFAIL("Failed to insert data into Games_data table.");
    }

    // Clean up
    query.finish(); // Finish the query to release resources
    db.close(); // Close the database connection
    QSqlDatabase::removeDatabase("testConnection"); // Remove the database connection

    delete multiPlayerWindow;
}



//QTEST_MAIN(TestMultiPlayerWindow_int)
#include "test_multiPlayerWindow_intigration.moc"
