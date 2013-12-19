#include <iostream>
#include <unistd.h>


#include "AutoControlSystems/heightautocontrolsystem.h"
#include "MeterSystems/heightmetersystem.h"
#include "ControlSystems/heightcontrolsystem.h"

#include "AutoControlSystems/headingangleautocontrolsystem.h"
#include "MeterSystems/headinganglemetersystem.h"
#include "ControlSystems/headinganglecontrolsystem.h"

using namespace std;

int main()
{

    double height = 0.0;
    double angle = 122.0;

    HeadingAngleControlSystem hac(&angle,0.04);
    HeadingAngleMeterSystem ham(&angle);
    HeadingAngleAutoControlSystem aac(&ham,&hac,angle);

    HeightControlSystem hc(&height, 0.04);
    HeightMeterSystem hm(&height);
    HeightAutoControlSystem ac(&hm,&hc,height);
    aac.start_control();
    ac.start_control();

    ac.set_height(1000);
    aac.set_angle(10);

    for(int i = 0; i < 10000; i++){
        cout << i << " ";
        cout<< angle << " ";
        usleep(100000);
        cout<< height << endl;
    }

    return 0;
}

