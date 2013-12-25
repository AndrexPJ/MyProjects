#include "headinganglemetersystem.h"

HeadingAngleMeterSystem::HeadingAngleMeterSystem()
{
    double default_value = 0.0;
    this->heading_angle = &default_value;
}

HeadingAngleMeterSystem::HeadingAngleMeterSystem(double *heading_angle){
    this->heading_angle = heading_angle;
}

double HeadingAngleMeterSystem::get_value(){
    return *(this->heading_angle);
}
