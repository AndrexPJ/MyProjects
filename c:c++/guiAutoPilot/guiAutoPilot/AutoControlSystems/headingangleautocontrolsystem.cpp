#include "headingangleautocontrolsystem.h"

HeadingAngleAutoControlSystem::HeadingAngleAutoControlSystem(HeadingAngleMeterSystem *meter_system, HeadingAngleControlSystem *control_system,
       double heading_angle_start_value, int time_interval_microsec, double angle_change_rate)
     : AutoControlSystem::AutoControlSystem(heading_angle_start_value){

    this->accuracy = 0.01;

    this->time_interval = time_interval_microsec;
    this->angle_change_rate = angle_change_rate;

    this->meter_system = meter_system;
    this->control_system = control_system;

}

HeadingAngleAutoControlSystem::~HeadingAngleAutoControlSystem() {
    AutoControlSystem::~AutoControlSystem();
}

void * HeadingAngleAutoControlSystem::control_function(void *controller){
    HeadingAngleAutoControlSystem *angle_controller = (HeadingAngleAutoControlSystem *)controller;

    double current_angle;
    double required_angle;

    while(true){
        current_angle = angle_controller->meter_system->get_value();
        required_angle = angle_controller->controlled_parameter;

        double difference = required_angle - current_angle;

        if(fabs(difference) >= angle_controller->accuracy)
            angle_controller->control_system->change_value(difference * angle_controller->angle_change_rate);

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


HeadingAngleAutoControlSystem* HeadingAngleAutoControlSystemFactory::produce_system(double *controlled_heading_angle, double start_heading_angle,
                                                                                    double change_rate){
    HeadingAngleControlSystem *headingAngleCS = new HeadingAngleControlSystem(controlled_heading_angle, change_rate);
    HeadingAngleMeterSystem *headingAngleMS = new HeadingAngleMeterSystem(controlled_heading_angle);
    return new HeadingAngleAutoControlSystem(headingAngleMS,headingAngleCS,start_heading_angle);
}
