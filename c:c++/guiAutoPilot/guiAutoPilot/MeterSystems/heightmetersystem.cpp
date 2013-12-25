#include "heightmetersystem.h"

HeightMeterSystem::HeightMeterSystem() : MeterSystem::MeterSystem()
{
    double default_value = 0.0;
    this->height = &default_value;
}

HeightMeterSystem::HeightMeterSystem(double *height) : MeterSystem::MeterSystem()
{
    this->height = height;
}


double HeightMeterSystem::get_value(){
 return *(this->height);
}
