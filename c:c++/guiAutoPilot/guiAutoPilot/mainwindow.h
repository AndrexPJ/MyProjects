#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "autopilotgui.h"
#include "planecontrolsystem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(AutoPilotGUI *gui,PlaneControlSystem *plane_c,QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PlaneControlSystem *plane_control;
    AutoPilotGUI *gui;
    void update();


};

#endif // MAINWINDOW_H
