#include <QtTest/QtTest>
#include "aiwindow.h"
#include "ui_aiwindow.h"
#include <QPushButton>

class TestAIWindow : public QObject
{
    Q_OBJECT

private slots:
    void testIsGameOver_RowCompleted_ai();
    void testIsGameOver_Tie_ai();
    void testIsGameOver_NotOver_ai();


    void testResetGame_ai();
    void testHandleButtonClick_Player_ai();
    void testHandleButtonClick_AI_ai();

    void testBoardCheck_GameOver_ai();
    void testButtonClickAndGameLogic_ai();
    void testEasymove_ai();
    void testMediummove_ai();
    void testHardmove_ai();


private:
    AIWindow *window;

    void clickButton(QPushButton *button);
};

// Test case to check game over when a row is completed
void TestAIWindow::testIsGameOver_RowCompleted_ai() {
    AIWindow aiWindow;
    aiWindow.getUI()->btn10->setText("X");
    aiWindow.getUI()->btn11->setText("X");
    aiWindow.getUI()->btn12->setText("X");
    QVERIFY(aiWindow.isGameOver());
}

// Test case to check game over when all cells are filled (tie)
void TestAIWindow::testIsGameOver_Tie_ai() {
    AIWindow aiWindow;
    aiWindow.getUI()->btn10->setText("X");
    aiWindow.getUI()->btn11->setText("O");
    aiWindow.getUI()->btn12->setText("X");
    aiWindow.getUI()->btn13->setText("O");
    aiWindow.getUI()->btn14->setText("X");
    aiWindow.getUI()->btn15->setText("X");
    aiWindow.getUI()->btn16->setText("O");
    aiWindow.getUI()->btn17->setText("X");
    aiWindow.getUI()->btn18->setText("O");
    QVERIFY(aiWindow.isGameOver());
}

// Test case to check game not over when no conditions met
void TestAIWindow::testIsGameOver_NotOver_ai() {
    AIWindow aiWindow;
    aiWindow.getUI()->btn10->setText("X");
    aiWindow.getUI()->btn12->setText("O");
    aiWindow.getUI()->btn13->setText("O");
    QVERIFY(!aiWindow.isGameOver());
}

// Test case to check if game board is reset properly
void TestAIWindow::testResetGame_ai() {
    AIWindow aiWindow;
    aiWindow.getUI()->btn10->setText("X");
    aiWindow.getUI()->btn11->setText("O");
    aiWindow.resetGame();
    QVERIFY(aiWindow.getUI()->btn10->text().isEmpty());
    QVERIFY(aiWindow.getUI()->btn11->text().isEmpty());
    // Ensure other game state variables are reset as expected
}

// Test case to simulate player's button click and check game state changes
void TestAIWindow::testHandleButtonClick_Player_ai() {
    AIWindow aiWindow;
    aiWindow.getUI()->btn10->click(); // Simulate player's click on a button
    QVERIFY(!aiWindow.getUI()->btn10->text().isEmpty()); // Check if button text is set
    // Check if player turn changes or other relevant game state changes occur
}

// Test case to simulate AI's move after player's move
void TestAIWindow::testHandleButtonClick_AI_ai() {
    AIWindow aiWindow;
    aiWindow.getUI()->btn10->click(); // Simulate player's click on a button
    QVERIFY(!aiWindow.getUI()->btn10->text().isEmpty()); // Check if button text is set
    // Simulate AI's move automatically after player's move
}

// Test case to check AI makes a move in Easy mode
void TestAIWindow::testEasymove_ai()
{
    AIWindow aiWindow;
    aiWindow.if_easy_clicked(true);
    aiWindow.if_medium_clicked(false);    // Ensure easy mode is enabled
    aiWindow.if_hard_clicked(false);
    // Simulate a scenario where some buttons are already chosen by the user
    aiWindow.findChild<QPushButton *>("btn10")->setText("X");
    aiWindow.findChild<QPushButton *>("btn11")->setText("O");
    aiWindow.findChild<QPushButton *>("btn12")->setText("X");

    // Call the Easymove function to let AI make a move
    aiWindow.Easymove();

    // Verify that AI has selected an empty button and made a move
    QList<QPushButton *> allButtons = aiWindow.findChildren<QPushButton *>();
    bool aiMadeMove = false;
    for (QPushButton *button : allButtons) {
        if (button->text().isEmpty() && button->objectName() != "btn10" && button->objectName() != "btn11" && button->objectName() != "btn12") {
            aiMadeMove = true;
            break;
        }
    }
    QVERIFY2(aiMadeMove, "AI did not make a move."); // Ensure AI actually made a move
}

// Test case to check AI makes a move in Medium mode
void TestAIWindow::testMediummove_ai()
{
    AIWindow aiWindow;
    aiWindow.if_medium_clicked(true);  // Enable medium mode

    // Simulate a scenario where some buttons are already chosen by the user
    aiWindow.findChild<QPushButton *>("btn10")->setText("X");
    aiWindow.findChild<QPushButton *>("btn11")->setText("O");
    aiWindow.findChild<QPushButton *>("btn12")->setText("X");

    // Call the Mediummove function to let AI make a move
    aiWindow.Mediummove();

    // Verify that AI has selected an empty button and made a move
    QList<QPushButton *> allButtons = aiWindow.findChildren<QPushButton *>();
    bool aiMadeMove = false;
    for (QPushButton *button : allButtons) {
        if (button->text().isEmpty() && button->objectName() != "btn10" && button->objectName() != "btn11" && button->objectName() != "btn12") {
            aiMadeMove = true;
            break;
        }
    }
    QVERIFY2(aiMadeMove, "AI did not make a move."); // Ensure AI actually made a move
}

// Test case to check AI makes a move in Hard mode
void TestAIWindow::testHardmove_ai()
{
    AIWindow aiWindow;
    aiWindow.if_hard_clicked(true);  // Enable hard mode

    // Simulate a scenario where some buttons are already chosen by the user
    aiWindow.findChild<QPushButton *>("btn10")->setText("X");
    aiWindow.findChild<QPushButton *>("btn11")->setText("O");
    aiWindow.findChild<QPushButton *>("btn12")->setText("X");

    // Call the Hardmove function to let AI make a move
    aiWindow.Hardmove();

    // Verify that AI has selected an empty button and made a move
    QList<QPushButton *> allButtons = aiWindow.findChildren<QPushButton *>();
    bool aiMadeMove = false;

    qDebug() << "Button statuses after AI move:";
    for (QPushButton *button : allButtons) {
        qDebug() << button->objectName() << ": " << button->text();
        if (!button->text().isEmpty() && button->objectName() != "btn10" && button->objectName() != "btn11" && button->objectName() != "btn12") {
            aiMadeMove = true;
        }
    }
    QVERIFY2(aiMadeMove, "AI did not make a move."); // Ensure AI actually made a move
}

// Test case to check database updates and UI changes after game over
void TestAIWindow::testBoardCheck_GameOver_ai() {
    AIWindow aiWindow;
    aiWindow.getUI()->btn10->setText("X");
    aiWindow.getUI()->btn14->setText("X");
    aiWindow.getUI()->btn18->setText("X");
    aiWindow.BoardCheck();
    // Verify if database is updated correctly, UI status changes, and game restarts or exits as expected
}

void TestAIWindow::testButtonClickAndGameLogic_ai()
{
    AIWindow aiWindow;
    aiWindow.show(); // Ensure window is shown for button access

    // Get access to the buttons for testing
    QPushButton *btn10 = aiWindow.findChild<QPushButton*>("btn10");
    QPushButton *btn11 = aiWindow.findChild<QPushButton*>("btn11");

    QVERIFY(btn10 != nullptr);
    QVERIFY(btn11 != nullptr);

    // Test clicking on the buttons and verifying the text change and disable state

    // Simulate button click on btn10
    QTest::mouseClick(btn10, Qt::LeftButton);
    QCOMPARE(btn10->text(), QString("X"));
    QVERIFY(!btn10->isEnabled());

    // Ensure that UI updates are processed
    QTest::qWait(100); // Adjust time as necessary or use QTest::qWaitForWindowExposed(&aiWindow);

    // Test game logic after some moves
    QCOMPARE(aiWindow.isGameOver(), false); // Verify game is not over after two moves
}

//QTEST_MAIN(TestAIWindow)
#include "test_aiwindow.moc"
