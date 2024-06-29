#ifndef MULTIPLAYERWINDOW_H
#define MULTIPLAYERWINDOW_H
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QMainWindow>
#include <QSet>
#include <QString>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QDialog>
//#include <QPainter>
namespace Ui {
class MultiPlayerWindow;
}

class MultiPlayerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MultiPlayerWindow(QWidget *parent = nullptr,const QString& s_username = "",const QString& username_2 = "");
    ~MultiPlayerWindow();
    bool isGameOver();
    void resetGame();
    void showDialog();
    void ButtonsOff();
    void openMainWindow(const QString& username);

    QString getCurrentPlayer() const;
    Ui::MultiPlayerWindow *ui;

    QString username_winner;
    QString m_username_multiplayer;
    QString m_username_2;
    QString currentPlayerSymbol;
    bool tie;

private slots:

    void handleResponse(bool msg);
    void handleButtonClick();

protected:
 //   void paintEvent(QPaintEvent *event) override; // Add paintEvent override declaration
    private:

};

#endif // MULTIPLAYERWINDOW_H
