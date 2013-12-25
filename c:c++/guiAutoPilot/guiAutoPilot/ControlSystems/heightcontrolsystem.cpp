#include "heightcontrolsystem.h"

HeightControlSystem::HeightControlSystem() : ControlSystem::ControlSystem()
{
    double default_value = 0.0;
    this->height = &default_value;
}

HeightControlSystem::HeightControlSystem(double *height, double change_rate) : ControlSystem::ControlSystem(){
    this->height = height;
    this->change_rate = change_rate;
}

void HeightControlSystem::set_value(double height){
    double current_heigth = *(this->height);
    *(this->height) = current_heigth + (height - current_heigth) * this->change_rate;
}

void HeightControlSystem::change_value(double height_difference){
     double current_heigth = *(this->height);
     *(this->height) = current_heigth + (height_difference) * this->change_rate;
}
