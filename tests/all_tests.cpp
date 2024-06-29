#ifdef RUNNING_TESTS

#include <QApplication>
#include <QCoreApplication>
#include <QtTest>

#include "test_aiwindow.cpp"
#include "test_aiwindow_intigration.cpp"
#include "test_multiplayerwindow.cpp"
#include "test_multiPlayerWindow_intigration.cpp"
#include "test_usersignuplogin.cpp"
//#include "test_loginwindow.cpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    int status = 0;

    // //Add each test class to the list of tests
    {
        TestAIWindow test1;
        status |= QTest::qExec(&test1, argc, argv);
    }
    {
        TestAIWindow_int test2;
        status |= QTest::qExec(&test2, argc, argv);
    }
    {
        TestMultiPlayerWindow test3;
        status |= QTest::qExec(&test3, argc, argv);
    }
    {
        TestMultiPlayerWindow_int test4;
        status |= QTest::qExec(&test4, argc, argv);
    }
    {
        TestUserSignupLogin test5;
        status |= QTest::qExec(&test5, argc, argv);
    }
    // {
    //     TestLoginWindow test5;
    //     status |= QTest::qExec(&test5, argc, argv);
    // }

    return status;
}

#endif
