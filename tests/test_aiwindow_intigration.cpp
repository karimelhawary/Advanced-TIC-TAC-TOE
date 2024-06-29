// File Two: test_aiwindow_intigration.cpp
#include <QtTest/QtTest>
#include "aiwindow.h"
#include "ui_aiwindow.h"
#include <QPushButton>

class TestAIWindow_int : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase_ai_int();
    //void cleanupTestCase_ai_int();
    void testGameInitialization_ai_int();
    void testButtonClick_ai_int();
    void testEasyMode_ai_int();
    void testMediumMode_ai_int();
    void testHardMode_ai_int();

private:
    AIWindow *aiWindow;
};

void TestAIWindow_int::initTestCase_ai_int()
{
    aiWindow = new AIWindow(nullptr, "test_user", "test_user@example.com");
    aiWindow->show();
}

// void TestAIWindow_int::cleanupTestCase_ai_int()
// {
//     delete aiWindow;
// }

void TestAIWindow_int::testGameInitialization_ai_int()
{
    AIWindow aiWindow;
    QLabel *label = aiWindow.findChild<QLabel*>("playerturn_1");
    QVERIFY(label != nullptr);
    QCOMPARE(label->text(), "Your Turn");
}

void TestAIWindow_int::testButtonClick_ai_int()
{
    QPushButton *button = aiWindow->findChild<QPushButton*>("btn10");
    QVERIFY(button != nullptr);

    QTest::mouseClick(button, Qt::LeftButton);

    QCOMPARE(button->text(), QString("X"));
    QVERIFY(!button->isEnabled());
}

void TestAIWindow_int::testEasyMode_ai_int()
{
    aiWindow->if_easy_clicked(true);

    aiWindow->resetGame();
    QPushButton *button = aiWindow->findChild<QPushButton*>("btn10");
    QTest::mouseClick(button, Qt::LeftButton);

    QVERIFY(button->text() == "X");
    QVERIFY(!button->isEnabled());

    // Simulate AI move
    QTest::qWait(1100); // Wait for AI move

    bool foundMove = false;
    for (int i = 11; i <= 18; ++i) {
        QPushButton *btn = aiWindow->findChild<QPushButton*>("btn" + QString::number(i));
        if (btn->text() == "O") {
            foundMove = true;
            break;
        }
    }

    QVERIFY(foundMove);
}

void TestAIWindow_int::testMediumMode_ai_int()
{
    aiWindow->if_medium_clicked(true);

    aiWindow->resetGame();
    QPushButton *button = aiWindow->findChild<QPushButton*>("btn10");
    QTest::mouseClick(button, Qt::LeftButton);

    QVERIFY(button->text() == "X");
    QVERIFY(!button->isEnabled());

    // Simulate AI move
    QTest::qWait(1100); // Wait for AI move

    bool foundMove = false;
    for (int i = 11; i <= 18; ++i) {
        QPushButton *btn = aiWindow->findChild<QPushButton*>("btn" + QString::number(i));
        if (btn->text() == "O") {
            foundMove = true;
            break;
        }
    }

    QVERIFY(foundMove);
}

void TestAIWindow_int::testHardMode_ai_int()
{
    aiWindow->if_hard_clicked(true);

    aiWindow->resetGame();
    QPushButton *button = aiWindow->findChild<QPushButton*>("btn10");
    QTest::mouseClick(button, Qt::LeftButton);

    QVERIFY(button->text() == "X");
    QVERIFY(!button->isEnabled());

    // Simulate AI move
    QTest::qWait(1100); // Wait for AI move

    bool foundMove = false;
    for (int i = 11; i <= 18; ++i) {
        QPushButton *btn = aiWindow->findChild<QPushButton*>("btn" + QString::number(i));
        if (btn->text() == "O") {
            foundMove = true;
            break;
        }
    }

    QVERIFY(foundMove);
}

//QTEST_MAIN(TestAIWindow_int)
#include "test_aiwindow_intigration.moc"


