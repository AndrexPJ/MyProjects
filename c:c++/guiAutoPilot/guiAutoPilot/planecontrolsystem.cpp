#include "planecontrolsystem.h"

PlaneControlSystem::PlaneControlSystem(AutoPilotSystem *main_autopilot, AutoPilotSystem *spare_autopilot,
                                       double *controlled_height, double *controlled_heading_angle)
{

    this->main_autopilot = main_autopilot;
    this->spare_autopilot = spare_autopilot;

    this->plane_height = controlled_height;
    this->plane_heading_angle = controlled_heading_angle;

    this->required_height = 0.0;
    this->required_heading_angle = 0.0;
    this->main_autopilot_state = false;
}

PlaneControlSystem::~PlaneControlSystem(){
        pthread_cancel(this->control_thread);
        this->main_autopilot->~AutoPilotSystem();
        this->spare_autopilot->~AutoPilotSystem();
}


void * PlaneControlSystem::control_function(void *controller){
    PlaneControlSystem *plane_controller = (PlaneControlSystem *)controller;


    while(true){
        if(plane_controller->main_autopilot_state){
            if(!plane_controller->main_autopilot->check_system()){
                plane_controller->spare_autopilot->set_height(plane_controller->required_height);
                plane_controller->spare_autopilot->set_heading_angle(plane_controller->required_heading_angle);
                plane_controller->main_autopilot->stop_control();
                sleep(2);
                plane_controller->spare_autopilot->start_control();
                plane_controller->main_autopilot_state = false;
                std::cout << "Started spare autopilot" << std::endl;
            }
        }
        else{
            if((!plane_controller->spare_autopilot->check_system()))
                {//std::cerr << "All autopilots died...." << std::endl;
            }
        }
    }
}

bool PlaneControlSystem::start_control(){
     this->main_autopilot->start_control();
     this->main_autopilot_state = true;
     pthread_create(&(this->control_thread),NULL,control_function,this);
     return true;
}

bool PlaneControlSystem::stop_control(){
    pthread_cancel(this->control_thread);
    this->main_autopilot->stop_control();
    this->spare_autopilot->stop_control();
    return true;
}


void PlaneControlSystem::set_height(double height){
    this->required_height = height;
    //if(this->main_autopilot_state)
        this->main_autopilot->set_height(this->required_height);
    //if(this->get_spare_autopilot_state())
        this->spare_autopilot->set_height(this->required_height);
}

void PlaneControlSystem::set_heading_angle(double heading_angle){
    this->required_heading_angle = heading_angle;
    //if(this->main_autopilot_state)
        this->main_autopilot->set_heading_angle(this->required_heading_angle);
    //else(this->get_spare_autopilot_state())
        this->spare_autopilot->set_heading_angle(this->required_heading_angle);
}

double PlaneControlSystem::get_height(){
    return *(this->plane_height);
}

double PlaneControlSystem::get_heading_angle(){
    return *(this->plane_heading_angle);
}

bool PlaneControlSystem::get_main_autopilot_state(){
    if(this->main_autopilot_state)
        return this->main_autopilot->check_system();
    else return false;
}

bool PlaneControlSystem::get_spare_autopilot_state(){
    return this->spare_autopilot->check_system();
}

void PlaneControlSystem::kill_main_autopilot(){
    this->main_autopilot->stop_control();
    this->main_autopilot_state = false;
}


