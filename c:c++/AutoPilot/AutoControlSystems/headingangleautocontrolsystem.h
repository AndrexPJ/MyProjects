#ifndef HEADINGANGLEAUTOCONTROLSYSTEM_H
#define HEADINGANGLEAUTOCONTROLSYSTEM_H

#include "AutoControlSystems/autocontrolsystem.h"
#include "MeterSystems/headinganglemetersystem.h"
#include "ControlSystems/headinganglecontrolsystem.h"



class HeadingAngleAutoControlSystem : public AutoControlSystem
{
private:
    int time_interval;
    double angle_change_rate;
    HeadingAngleMeterSystem *meter_system;
    HeadingAngleControlSystem *control_system;

    static void *control_function(void *controller);

public:
    HeadingAngleAutoControlSystem();
    HeadingAngleAutoControlSystem(HeadingAngleMeterSystem *meter_system, HeadingAngleControlSystem *control_system,
            double heading_angle_start_value = 0, int time_interval_microsec = 100000, double angle_change_rate = 1.0);
    bool set_angle(double angle);
    double get_angle();
    bool start_control();
    bool stop_control();
};

#endif // HEADINGANGLEAUTOCONTROLSYSTEM_H
