#include <QApplication>

#include "autopilotgui.h"
#include "planecontrolsystem.h"
#include "iostream"
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    double height = 0.0;
    double angle = 0.0;

    AutoPilotSystem main_autopilot = AutoPilotSystemFactory::build_system(&height,height,&angle,angle);
    AutoPilotSystem spare_autopilot = AutoPilotSystemFactory::build_system(&height,height,&angle,angle);



    MainWindow *mw = new MainWindow(&main_autopilot,&spare_autopilot, &height, &angle);

    mw->show();


    return a.exec();
}
