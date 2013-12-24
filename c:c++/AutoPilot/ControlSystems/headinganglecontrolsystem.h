#ifndef HEADINGANGLECONTROLSYSTEM_H
#define HEADINGANGLECONTROLSYSTEM_H

#include "ControlSystems/controlsystem.h"

class HeadingAngleControlSystem : public ControlSystem
{
private:
    double *heading_angle;
    double change_rate;
public:
    HeadingAngleControlSystem();
    HeadingAngleControlSystem(double *heading_angle, double change_rate = 1.0);
    void set_value(double heading_angle);
    void change_value(double heading_angle_difference);
};

#endif // HEADINGANGLECONTROLSYSTEM_H
