#include <QApplication>

#include "autopilotgui.h"
#include "planecontrolsystem.h"
int main(int argc, char *argv[])
{

    double height = 5000.0;
    double angle = 112.01;

    AutoPilotSystem main_autopilot = AutoPilotSystemFactory::build_system(&height,height,&angle,angle);
    AutoPilotSystem spare_autopilot = AutoPilotSystemFactory::build_system(&height,height,&angle,angle);

    PlaneControlSystem plane_cs(&main_autopilot,&spare_autopilot,&height,&angle);

    QApplication a(argc, argv);

    AutoPilotGUI gui(&height,&angle);

    gui.show();


    return a.exec();
}
