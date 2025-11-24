#include "dialog.h"
#include "ui_dialog.h"
#include <fstream>

extern int sec_to_loose_glob;
extern int apple_to_win_glob;
extern bool need_timer;
extern bool need_apple;
extern bool needplay;
std::string txtName = "opt.txt";
void Dialog::startOperations(){
    std::string temp;

    std::ifstream in(txtName);
    if (in.is_open())
    {
        int a = 0;
        while (std::getline(in, temp))
        {
            if (a==0){
                sec_to_loose_glob = std::stoi(temp);
            }
            if (a==1){
                apple_to_win_glob = std::stoi(temp);
            }
            if (a==2){
                need_timer = std::stoi(temp);
            }
            if (a==3){
                need_apple = std::stoi(temp);
            }
            if (a==4){
                needplay = std::stoi(temp);
            }
            a++;
        }

        in.close();

    }
    if(need_apple) ui->checkBox->click();
    ui->spinBox->setValue(apple_to_win_glob);

    if(need_timer) ui->checkBox_2->click();
    ui->spinBox_2->setValue(sec_to_loose_glob);

}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    startOperations();
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
    std::ofstream out;
    out.open(txtName);
    if (out.is_open())
    {
        out << sec_to_loose_glob << std::endl
            << apple_to_win_glob << std::endl
            << need_timer << std::endl
            << need_apple << std::endl
            << needplay << std::endl;
    }
    out.close();
    close();
}


