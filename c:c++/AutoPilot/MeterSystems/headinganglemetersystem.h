#ifndef HEADINGANGLEMETERSYSTEM_H
#define HEADINGANGLEMETERSYSTEM_H

#include "MeterSystems/metersystem.h"

class HeadingAngleMeterSystem : public MeterSystem
{
private:
    double *heading_angle;
public:
    HeadingAngleMeterSystem();
    HeadingAngleMeterSystem(double *heading_angle);
    double get_value();
};

#endif // HEADINGANGLEMETERSYSTEM_H
