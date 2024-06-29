#include <QtTest/QtTest>
#include "multiplayerwindow.h"
#include "ui_multiplayerwindow.h"
#include <QPushButton>
#include <iostream>

class TestMultiPlayerWindow : public QObject {
    Q_OBJECT

private slots:
    void initTestCase_mu();

    void testIsGameOver_mu();
    void testResetGame_mu();
    void tetestHandleButtonClick_mu();

private:
    MultiPlayerWindow *window;
};

void TestMultiPlayerWindow::initTestCase_mu() {
    window = new MultiPlayerWindow(nullptr, "player1", "player2");
}



void TestMultiPlayerWindow::testIsGameOver_mu() {
    // Set up a winning condition
    window->ui->btn1->setText("X");
    window->ui->btn2->setText("X");
    window->ui->btn3->setText("X");

    QVERIFY(window->isGameOver() == true);

    // Reset buttons and check for a tie
    window->resetGame();
    window->ui->btn1->setText("X");
    window->ui->btn2->setText("O");
    window->ui->btn3->setText("X");
    window->ui->btn4->setText("O");
    window->ui->btn5->setText("X");
    window->ui->btn6->setText("O");
    window->ui->btn7->setText("O");
    window->ui->btn8->setText("X");
    window->ui->btn9->setText("O");

    QVERIFY(window->isGameOver() == true);
}

void TestMultiPlayerWindow::testResetGame_mu() {
    window->resetGame();

    // Check if all buttons are cleared and enabled
    QList<QPushButton *> buttons = window->findChildren<QPushButton *>();
    foreach (QPushButton *button, buttons) {
        QVERIFY(button->text().isEmpty());
        QVERIFY(button->isEnabled());
    }
    // Check if current player symbol is reset
    QVERIFY(window->currentPlayerSymbol == "X");
}

void TestMultiPlayerWindow::tetestHandleButtonClick_mu() {
    window = new MultiPlayerWindow(nullptr, "player1", "player2");

    // Spy on the clicked signal of button 1
    QSignalSpy spy(window->ui->btn1, SIGNAL(clicked()));
    // Simulate a button click
    QTest::mouseClick(window->ui->btn1, Qt::LeftButton);

    // Verify that the button text is set correctly and button is disabled
    QCOMPARE(window->ui->btn1->text(), QString("X"));
    QVERIFY(!window->ui->btn1->isEnabled());

    // Verify that the signal was emitted
    QCOMPARE(spy.count(), 1);

    // Simulate another button click
    QTest::mouseClick(window->ui->btn2, Qt::LeftButton);

    QCOMPARE(window->ui->btn2->text(), QString("O"));
    QVERIFY(!window->ui->btn2->isEnabled());

    delete window;
}



//QTEST_MAIN(TestMultiPlayerWindow)
#include "test_multiplayerwindow.moc"
