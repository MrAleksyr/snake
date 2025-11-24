#include "dialog.h"
#include "ui_dialog.h"

extern int sec_to_loose_glob;
extern int apple_to_win_glob;
extern bool need_timer;
extern bool need_apple;
extern bool needplay;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_spinBox_valueChanged(int arg1)
{
    apple_to_win_glob = ui->spinBox->value();
}

void Dialog::on_spinBox_2_valueChanged(int arg1)
{
    sec_to_loose_glob = ui->spinBox_2->value();
}

void Dialog::on_checkBox_2_toggled(bool checked)
{
    need_timer = checked;
}

void Dialog::on_checkBox_toggled(bool checked)
{
    need_apple = checked;
}

void Dialog::on_pushButton_clicked()
{
    close();
}


