#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include "dialog.h"

extern int sec_to_loose_glob;
extern int apple_to_win_glob;
extern bool need_timer;
extern bool need_apple;
extern bool needplay;

int seconds_to_loose = 20;
int snakeLong = 1;
bool timer_start = 0;
const int mapSize = 100;
int map[mapSize];
unsigned int headpos = 45;
int applepos = 5;
void MainWindow::startOperations(){
    for(int i = 0; i < mapSize; i++){
        map[i] = 0;
    }
    map[headpos-1] = 1;
    map[applepos - 1] = -1;

    hide();
    if(!dialog){
        dialog = new Dialog(this);
    }
    //dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->exec();
    seconds_to_loose = sec_to_loose_glob;
    timer_start = !need_timer;




    QString temp = "Time to loose: ";
    QString temp_s = QString::number(seconds_to_loose);
    temp+=temp_s;
    QLabel* label;
    QString buttonName = QString("label_101");
    label = findChild<QLabel*>(buttonName);
    if(label){
        label->setText(temp);
    }else QMessageBox::information(nullptr, "ERROR", "LABEL NOT FOUND");

}

void MainWindow::reRender(){
    QLabel* label;
    for(int indexpos = 1; indexpos < mapSize+1; indexpos++){
        if(indexpos!=1){
            QString buttonName = QString("label_%1").arg(indexpos);
            label = findChild<QLabel*>(buttonName);
        } else {
            QString buttonName = QString("label");
            label = findChild<QLabel*>(buttonName);
        }
        if(label){
            if(map[indexpos-1]==-1){label->setText("A");}
            else if(map[indexpos-1]==0){label->setText(" ");}
            else if(map[indexpos-1]==1){label->setText("O");}
            else if(map[indexpos-1]>1){
                map[indexpos-1]++;
                if(map[indexpos-1]<=snakeLong+1)
                {
                    label->setText("o");

                }
                else label->setText(" ");
            }

        } else QMessageBox::information(nullptr, "ERROR", "LABEL NOT FOUND");
    }


}

void MainWindow::slotTimerAlarm()
{

    if(seconds_to_loose>0){
        seconds_to_loose--;
        QString temp = "Time to loose: ";
        QString temp_s = QString::number(seconds_to_loose);
        temp+=temp_s;
        ui->label_101->setText(temp);
    }
    else {
        QMessageBox::information(nullptr, "LOSE", "LOOOOOOOSE");
        QApplication::quit();
    }
    //ui->label_101->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    bool boom = 0;
    if(!timer_start){
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
        timer->start(1000);
        timer_start = 1;
    }
    if(e->key()==Qt::Key_W) {
        if(headpos>10){
            map[headpos-1]++;
            headpos-=10;
            if((map[headpos-1]<=snakeLong+1)&&(map[headpos-1]>0)){boom=1;}
            map[headpos-1] = 1;
        }
        else return;
    }
    else if(e->key()==Qt::Key_D) {
        if((headpos-1)%10<9){
            map[headpos-1]++;
            headpos+=1;
            if((map[headpos-1]<=snakeLong+1)&&(map[headpos-1]>0)){boom=1;}
            map[headpos-1] = 1;
        }
        else return;
    }
    else if(e->key()==Qt::Key_S) {
        if(headpos<=90){
            map[headpos-1]++;
            headpos+=10;
            if((map[headpos-1]<=snakeLong+1)&&(map[headpos-1]>0)){boom=1;}
            map[headpos-1] = 1;
        }
        else return;
    }
    else if(e->key()==Qt::Key_A) {
        if((headpos-1)%10>0){
            map[headpos-1]++;
            headpos-=1;
            if((map[headpos-1]<=snakeLong+1)&&(map[headpos-1]>0)){boom=1;}
            map[headpos-1] = 1;
        }
        else return;
    }
    else if(e->key()==Qt::Key_F4){
        int temppos = 0;
        srand(time(0));

        while((temppos==0)||((map[temppos-1]<snakeLong)&&(map[temppos-1]!=0)))  {
            temppos = (rand()%101)+1;
        }
        applepos = temppos;
        map[applepos-1] = -1;


    }
    if(headpos == applepos){
        snakeLong +=1;
        int temppos = 0;
        srand(time(0));
        while((temppos==0)||((map[temppos-1]<snakeLong)&&(map[temppos-1]!=0)))  {
            temppos = (rand()%100)+1;
        }
        applepos = temppos;
        map[applepos-1] = -1;

        QString temp = "Time to loose: ";
        QString temp_s = QString::number(seconds_to_loose);
        temp+=temp_s;
        temp+=" + 10 sec";
        QLabel* label;
        QString buttonName = QString("label_101");
        label = findChild<QLabel*>(buttonName);
        if(label){
            label->setText(temp);
        }else QMessageBox::information(nullptr, "ERROR", "LABEL NOT FOUND");
        seconds_to_loose+=10;
    }
    reRender();
    if(snakeLong>100){
        QMessageBox::information(nullptr, "WIN", "WINWINWINWINWIN");
        QApplication::quit();
    }
    if(boom){
        QMessageBox::information(nullptr, "LOSE", "LOOOOOOOSE");
        QApplication::quit();
    }

}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    dialog(nullptr)
{
    ui->setupUi(this);
    startOperations();
    reRender();
    //ui->label_101->setText(QTime::currentTime().toString("hh:mm:ss"));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete dialog;
}



void MainWindow::on_pushButton_clicked()
{
    /*
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(1000);
*/
}

