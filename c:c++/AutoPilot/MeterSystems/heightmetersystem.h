#ifndef HEIGHTMETERSYSTEM_H
#define HEIGHTMETERSYSTEM_H

#include "MeterSystems/metersystem.h"

class HeightMeterSystem : public MeterSystem
{
private:
    double *height;
public:
    HeightMeterSystem();
    HeightMeterSystem(double *height);
    double get_value();
};

#endif // HEIGHTMETERSYSTEM_H
