#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Dialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void startOperations();

    void reRender();

    void slotTimerAlarm();


protected:
    void keyPressEvent(QKeyEvent *e) override;
private:
    Ui::MainWindow *ui;
    Dialog *dialog;
    QTimer *timer;
};
#endif // MAINWINDOW_H
