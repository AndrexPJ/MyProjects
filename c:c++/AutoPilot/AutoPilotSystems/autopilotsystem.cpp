#include "autopilotsystem.h"

AutoPilotSystem::AutoPilotSystem(HeightAutoControlSystem *heightACS, HeadingAngleAutoControlSystem *headingAngleACS){
    this->headingAngleACS = headingAngleACS;
    this->heightACS = heightACS;

    this->headingAngleCS_thread = &(this->headingAngleACS->control_thread);
    this->heigthCS_thread = &(this->heightACS->control_thread);
}


bool AutoPilotSystem::set_height(double height){
    return this->heightACS->set_height(height);
}

bool AutoPilotSystem::set_heading_angle(double heading_angle){
    return this->headingAngleACS->set_angle(heading_angle);
}

bool AutoPilotSystem::check_system(){
    return (this->headingAngleACS->check_system() && this->heightACS->check_system() &&
            (pthread_kill(*(this->headingAngleCS_thread), 0) != ESRCH) && (pthread_kill(*(this->heigthCS_thread), 0) != ESRCH));
}

bool AutoPilotSystem::start_control(){
    return (this->headingAngleACS->start_control() && this->heightACS->start_control());
}

bool AutoPilotSystem::stop_control(){
    return (this->headingAngleACS->stop_control() && this->heightACS->stop_control());
}

AutoPilotSystem AutoPilotSystemFactory::build_system(double *controlled_height, double start_height,
                                                     double *controlled_heading_angle, double start_heding_angle,
                                                     double height_change_rate, double heading_angle_change_rate)
{
    HeadingAngleAutoControlSystem *HAACS = HeadingAngleAutoControlSystemFactory::produce_system
            (controlled_heading_angle,start_heding_angle,heading_angle_change_rate);

    HeightAutoControlSystem *HGTHACS = HeightAutoControlSystemFactory::produce_system
            (controlled_height,start_height,height_change_rate);

    return AutoPilotSystem::AutoPilotSystem(HGTHACS,HAACS);

}


