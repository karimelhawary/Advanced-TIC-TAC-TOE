#include "chooseaiwindow.h"
#include "ui_chooseaiwindow.h"
#include <QPixmap>


ChooseAIWindow::ChooseAIWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChooseAIWindow)
{
    ui->setupUi(this);
    QPixmap pix4("C:/Users/Kareem/Desktop/Advanced Tic Tac Toe(GridMasters)/Easy.png");
    ui->label_pic_4->setPixmap(pix4);
    QPixmap pix5("C:/Users/Kareem/Desktop/Advanced Tic Tac Toe(GridMasters)/Midium.png");
    ui->label_pic_5->setPixmap(pix5);
    QPixmap pix6("C:/Users/Kareem/Desktop/Advanced Tic Tac Toe(GridMasters)/Hard.png");
    ui->label_pic_6->setPixmap(pix6);

}

ChooseAIWindow::~ChooseAIWindow()
{
    delete ui;
}

void ChooseAIWindow::on_easy_btn_clicked(){
    emit easy_clicked(true);
    emit medium_clicked(false);
    emit hard_clicked(false);
    close();
}

void ChooseAIWindow::on_medium_btn_clicked(){
    emit easy_clicked(false);
    emit medium_clicked(true);
    emit hard_clicked(false);
    close();
}

void ChooseAIWindow::on_hard_btn_clicked(){
    emit easy_clicked(false);
    emit medium_clicked(false);
    emit hard_clicked(true);
    close();
}
