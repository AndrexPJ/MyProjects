#include <iostream>
#include <unistd.h>

#include "AutoPilotSystems/autopilotsystem.h"

using namespace std;

int main()
{

    double height = 0.0;
    double angle = 122.0;

    AutoPilotSystem auto_pilot = AutoPilotSystemFactory::build_system(&height,height,&angle,angle);

    auto_pilot.start_control();

    auto_pilot.set_heading_angle(0.1);
    auto_pilot.set_height(1000);

    for(int i = 0; i < 10000; i++){
        cout << i << " ";
        cout<< angle << " ";
        cout<< height << " ";
        cout<< auto_pilot.check_system() << endl;
        usleep(100000);
    }

    return 0;
}

