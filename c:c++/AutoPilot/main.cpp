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
    HeightControlSystem hc(&height, 0.01);
    HeightMeterSystem hm(&height);
    HeightAutoControlSystem ac(&hm,&hc,height);

    ac.start_control();
    ac.set_height(1000);
    for(int i = 0; i < 10000; i++){
        cout << i << " ";
        cout<< height << " ";
        usleep(100000);
        cout<< height << endl;
    }

    return 0;
}

