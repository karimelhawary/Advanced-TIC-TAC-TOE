#ifndef AIWINDOW_H
#define AIWINDOW_H

#include <QDialog>
//#include <QPainter>
namespace Ui {
class AIWindow;
}

class AIWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AIWindow(QWidget *parent = nullptr,const QString& username_ai = "", const QString& email_ai = "");
    ~AIWindow();
    bool isGameOver();
    void if_easy_clicked(bool easy);
    void if_medium_clicked(bool medium);
    void if_hard_clicked(bool hard);
    void resetGame();
    void showDialog();

    void Easymove();
    void Mediummove();
    bool checkwin(QString sympol);
    void Hardmove();
    void BoardCheck();
    void openMainWindow(const QString& username);
    Ui::AIWindow *ui;
    Ui::AIWindow* getUI() const { return ui; }

private slots:
    void showChooseDefficulity();
    void handleResponse(bool msg);
    void handleButtonClick();
    void ButtonsOff();
    int MiniMax(bool maximizingPlayer, int depth, int alpha, int beta);
    bool isfull();

private:
    QString m_username_ai;
    QString m_email_ai;

};

#endif // AIWINDOW_H
