#include "headingangleautocontrolsystem.h"

HeadingAngleAutoControlSystem::HeadingAngleAutoControlSystem(HeadingAngleMeterSystem *meter_system, HeadingAngleControlSystem *control_system,
       double heading_angle_start_value, int time_interval_microsec, double angle_change_rate)
     : AutoControlSystem::AutoControlSystem(heading_angle_start_value){

    this->time_interval = time_interval_microsec;
    this->angle_change_rate = angle_change_rate;

    this->meter_system = meter_system;
    this->control_system = control_system;

}


void * HeadingAngleAutoControlSystem::control_function(void *controller){
    HeadingAngleAutoControlSystem *angle_controller = (HeadingAngleAutoControlSystem *)controller;

    double current_angle;
    double required_angle;

    while(true){
        current_angle = angle_controller->meter_system->get_value();
        required_angle = angle_controller->controlled_parameter;
        angle_controller->control_system->set_value((required_angle - current_angle) * angle_controller->angle_change_rate
                                                    + current_angle);
        usleep(angle_controller->time_interval);
    }
}

bool HeadingAngleAutoControlSystem::set_angle(double angle){
    this->controlled_parameter = angle;
    return true;
}

double HeadingAngleAutoControlSystem::get_angle(){
    return this->controlled_parameter;
}

bool HeadingAngleAutoControlSystem::start_control(){
    return AutoControlSystem::start_control(this->control_function,(void*)this);
}

bool HeadingAngleAutoControlSystem::stop_control(){
    return AutoControlSystem::stop_control();
}
