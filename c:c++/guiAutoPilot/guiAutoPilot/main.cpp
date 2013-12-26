#include <QApplication>

#include "autopilotgui.h"
#include "planecontrolsystem.h"
#include "iostream"
#include "mainwindow.h"
int main(int argc, char *argv[])
{

    double height = 10.0;
    double angle = 1.01;

    AutoPilotSystem main_autopilot = AutoPilotSystemFactory::build_system(&height,height,&angle,angle);
    AutoPilotSystem spare_autopilot = AutoPilotSystemFactory::build_system(&height,height,&angle,angle);

    PlaneControlSystem plane_cs(&main_autopilot,&spare_autopilot,&height,&angle);

    QApplication a(argc, argv);

    AutoPilotGUI gui(&height,&angle);

    MainWindow mw(&gui,&plane_cs);

    plane_cs.start_control();
    plane_cs.set_heading_angle(184.1);
    plane_cs.set_height(5000);

    gui.set_angle(184.1);
    gui.set_height(5000);


    mw.show();


    return a.exec();
}
