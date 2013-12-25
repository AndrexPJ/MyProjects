#include <iostream>
#include <unistd.h>

#include "planecontrolsystem.h"
using namespace std;

int main()
{

    double height = 0.0;
    double angle = 122.0;

    AutoPilotSystem main_autopilot = AutoPilotSystemFactory::build_system(&height,height,&angle,angle);
    AutoPilotSystem spare_autopilot = AutoPilotSystemFactory::build_system(&height,height,&angle,angle);

    PlaneControlSystem plane_cs(&main_autopilot,&spare_autopilot,&height,&angle);

    plane_cs.start_control();
    plane_cs.set_height(1000);
    plane_cs.set_heading_angle(10);

    for(int i = 0; i < 10000; i++){
        cout << i << " ";
        cout << height << " ";
        cout << angle << " ";
        cout << plane_cs.get_main_autopilot_state() << " ";
        cout << plane_cs.get_spare_autopilot_state() << endl;
        if(i==50)
            plane_cs.kill_main_autopilot();

        usleep(100000);
    }

    return 0;
}

