#ifndef CHOOSEAIWINDOW_H
#define CHOOSEAIWINDOW_H
#include <QDialog>
#include "mainwindow.h"
//#include <QPainter>
namespace Ui {
class ChooseAIWindow;
}

class ChooseAIWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseAIWindow(QWidget *parent = nullptr);
    ~ChooseAIWindow();

signals:
    void easy_clicked(bool easybtn);
    void medium_clicked(bool mediumbtn);
    void hard_clicked(bool hardbtn);

private slots:
    void on_easy_btn_clicked();
    void on_medium_btn_clicked();
    void on_hard_btn_clicked();
private:
    Ui::ChooseAIWindow *ui;
};

#endif // CHOOSEAIWINDOW_H
