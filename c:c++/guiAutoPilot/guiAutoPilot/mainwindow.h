#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include "autopilotgui.h"
#include "planecontrolsystem.h"
#include <csignal>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(AutoPilotSystem *main_autopilot,AutoPilotSystem *spare_autopilot, double *height, double *angle, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    PlaneControlSystem *plane_control;
    AutoPilotSystem *main_autopilot;
    AutoPilotSystem *spare_autopilot;
    StateButton *main_ap_b;
    StateButton *spare_ap_b;
    int main_ap_state;
    int spare_ap_state;

    bool started,random_state;
    double *height,*angle;

public slots:
    void set_height(int height);
    void set_angle(int angle);
    void start();
    void stop();
    void kill_main_ap();
    void update();
    void random();
    void random_start_stop();


};

#endif // MAINWINDOW_H
