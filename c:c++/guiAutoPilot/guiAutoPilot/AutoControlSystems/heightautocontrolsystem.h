#ifndef HEIGHTAUTOCONTROLSYSTEM_H
#define HEIGHTAUTOCONTROLSYSTEM_H

#include "AutoControlSystems/autocontrolsystem.h"
#include "MeterSystems/heightmetersystem.h"
#include "ControlSystems/heightcontrolsystem.h"


class HeightAutoControlSystem : public AutoControlSystem
{
private:
    int time_interval;
    double height_change_rate;
    HeightMeterSystem *meter_system;
    HeightControlSystem *control_system;

    static void *control_function(void *controller);

public:
    HeightAutoControlSystem(HeightMeterSystem *meter_system, HeightControlSystem *control_system,
            double height_start_value = 0, int time_interval_microsec = 100000, double height_change_rate = 1.0);
    ~HeightAutoControlSystem();
    bool set_height(double height);
    double get_height();
    bool start_control();
    bool stop_control();
};


class HeightAutoControlSystemFactory{
public:
    static HeightAutoControlSystem * produce_system(double *controlled_height,double start_height, double change_rate = 1.0);

};

#endif // HEIGHTAUTOCONTROLSYSTEM_H
