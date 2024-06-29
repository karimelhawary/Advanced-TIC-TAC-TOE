#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL(click()), this, SLOT(openMainWindow()));
}

Dialog::~Dialog()
{
    delete ui;
}

// void Dialog::openMainWindow()
// {
//     mainwindow = new MainWindow();
//     mainwindow->show();
// }

void Dialog::on_yesbtn_clicked()
{
    // Emit signal with true when "Yes" button is clicked
    emit response(true);
    close(); // Close the dialog
}

void Dialog::on_pushButton_2_clicked()
{
    // Emit signal with false when "Button 2" is clicked
    emit response(false);
    //openMainWindow();
    close(); // Close the dialog
}
