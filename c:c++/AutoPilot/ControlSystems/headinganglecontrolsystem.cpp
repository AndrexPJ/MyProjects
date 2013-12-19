#include "headinganglecontrolsystem.h"

HeadingAngleControlSystem::HeadingAngleControlSystem()
{
    double default_value = 0.0;
    this->heading_angle = &default_value;
}

HeadingAngleControlSystem::HeadingAngleControlSystem(double *heading_angle, double change_rate){
    this->heading_angle = heading_angle;
    this->change_rate = change_rate;
}


void HeadingAngleControlSystem::set_value(double heading_angle){
    double current_heading_angle = *(this->heading_angle);
    *(this->heading_angle) = current_heading_angle + (heading_angle - heading_angle) * this->change_rate;
}
