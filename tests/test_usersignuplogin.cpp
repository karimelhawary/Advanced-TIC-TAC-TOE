#include <QtTest/QtTest>
#include "signupwindow.h"
#include "ui_signupwindow.h"

class TestUserSignupLogin : public QObject
{
    Q_OBJECT

private slots:
    void testSignup();
};

void TestUserSignupLogin::testSignup()
{
    // Ensure the database is clean before starting the test
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::database("qt_sql_default_connection").close();
        QSqlDatabase::removeDatabase("qt_sql_default_connection");

    }

    // Setup SignupWindow
    SignupWindow signupWindow;

    // Set UI values
    signupWindow.ui->username_2->setText("GRID MASTERSssss");
    signupWindow.ui->password_2->setText("password");
    signupWindow.ui->mail_2->setText("GRID_MASTERSsss@mail.com");
    signupWindow.ui->first_name_2->setText("GRID MASTERS");
    signupWindow.ui->last_name_2->setText("GRID MASTERS");
    signupWindow.ui->year_2->setText("2003");
    signupWindow.ui->month_2->setText("09");
    signupWindow.ui->day_2->setText("03");

    // Simulate sign up button click
    signupWindow.on_sign_up_clicked();

    // Check the message field for the success or error message
    QString messageText = signupWindow.ui->message->text();
    if (!messageText.isEmpty()) {
        qDebug() << "Sign up message:" << messageText;
       // QVERIFY2(messageText != "Error: Email already exists.", "Email already exists in the database.");
        // QVERIFY2(messageText == "", qPrintable("Error: Sign Up failed with message: " + messageText));
    } else {
        // Verify that data is inserted into the database
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:\\Users\\user\\OneDrive\\Desktop\\New folder\\TICTACTOE-main\\TICTACTOE-main\\tictactoe.db");
        if (!db.open()) {
            QFAIL("Failed to open database for verification.");
        }

        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM Players_Data WHERE username = :username");
        query.bindValue(":username", "testuser");

        if (!query.exec() || !query.next()) {
            QFAIL("Failed to execute query or retrieve result.");
        }

        int count = query.value(0).toInt();
        QCOMPARE(count, 1);

        db.close();
    }
}

//QTEST_MAIN(TestUserSignupLogin)
#include "test_usersignuplogin.moc"
