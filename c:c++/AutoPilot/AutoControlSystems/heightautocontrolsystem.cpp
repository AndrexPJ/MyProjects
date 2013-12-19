#include "AutoControlSystems/heightautocontrolsystem.h"

HeightAutoControlSystem::HeightAutoControlSystem(HeightMeterSystem *meter_system, HeightControlSystem *control_system,
      double height_start_value, int time_interval_microsec, double height_change_rate)
    : AutoControlSystem::AutoControlSystem(height_start_value){

    this->time_interval = time_interval_microsec;
    this->height_change_rate = height_change_rate;

    this->meter_system = meter_system;
    this->control_system = control_system;
}


void * HeightAutoControlSystem::control_function(void *controller){
    HeightAutoControlSystem *height_controller = (HeightAutoControlSystem *)controller;

    double current_height;
    double required_height;
    while(true){
        current_height = height_controller->meter_system->get_value();
        required_height = height_controller->controlled_parameter;
        height_controller->control_system->set_value((required_height - current_height) * height_controller->height_change_rate
                                                        + current_height);
        usleep(height_controller->time_interval);

    }
}

bool HeightAutoControlSystem::set_height(double height){
    this->controlled_parameter = height;
    return true;
}

double HeightAutoControlSystem::get_height(){
    return this->controlled_parameter;
}

bool HeightAutoControlSystem::start_control() {
   return AutoControlSystem::start_control(this->control_function,(void*)this);
}

bool HeightAutoControlSystem::stop_control(){
    return AutoControlSystem::stop_control();
}


