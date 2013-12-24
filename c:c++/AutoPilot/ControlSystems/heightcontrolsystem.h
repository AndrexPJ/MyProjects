#ifndef HEIGHTCONTROLSYSTEM_H
#define HEIGHTCONTROLSYSTEM_H

#include "ControlSystems/controlsystem.h"

class HeightControlSystem : public ControlSystem
{
private:
    double *height;
    double change_rate;
public:
    HeightControlSystem();
    HeightControlSystem(double *height, double change_rate = 1.0);
    void set_value(double height);
    void change_value(double height_difference);
};

#endif // HEIGHTCONTROLSYSTEM_H
