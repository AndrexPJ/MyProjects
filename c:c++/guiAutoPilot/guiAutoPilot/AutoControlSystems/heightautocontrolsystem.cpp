#include "AutoControlSystems/heightautocontrolsystem.h"

HeightAutoControlSystem::HeightAutoControlSystem(HeightMeterSystem *meter_system, HeightControlSystem *control_system,
      double height_start_value, int time_interval_microsec, double height_change_rate)
    : AutoControlSystem::AutoControlSystem(height_start_value){

    this->accuracy = 0.01;

    this->time_interval = time_interval_microsec;
    this->height_change_rate = height_change_rate;

    this->meter_system = meter_system;
    this->control_system = control_system;
}

HeightAutoControlSystem::~HeightAutoControlSystem(){
    AutoControlSystem::~AutoControlSystem();
}

void * HeightAutoControlSystem::control_function(void *controller){
    HeightAutoControlSystem *height_controller = (HeightAutoControlSystem *)controller;

    double current_height;
    double required_height;
    while(true){
        current_height = height_controller->meter_system->get_value();
        required_height = height_controller->controlled_parameter;

        double difference = required_height - current_height;

        if(fabs(difference) >= height_controller->accuracy)
            height_controller->control_system->change_value(difference * height_controller->height_change_rate);

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


HeightAutoControlSystem * HeightAutoControlSystemFactory::produce_system(double *controlled_height, double start_height, double change_rate){
    HeightControlSystem *heightCS = new HeightControlSystem(controlled_height, change_rate);
    HeightMeterSystem *heightMS = new HeightMeterSystem(controlled_height);
    return new HeightAutoControlSystem(heightMS,heightCS,start_height);
}
