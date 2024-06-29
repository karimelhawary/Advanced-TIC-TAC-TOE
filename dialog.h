#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include "mainwindow.h"
#include <QPainter>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
   //  void openMainWindow();

private:
    MainWindow *mainwindow;

signals:
    void response(bool msg);

private slots:
    void on_yesbtn_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
