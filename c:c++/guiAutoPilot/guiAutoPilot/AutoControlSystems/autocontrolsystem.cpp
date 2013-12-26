#include "autocontrolsystem.h"

AutoControlSystem::AutoControlSystem(double controlled_parameter_start_value){
    this->controlled_parameter = controlled_parameter_start_value;
}

AutoControlSystem::~AutoControlSystem(){
    pthread_cancel(this->control_thread);
}

bool AutoControlSystem::start_control(void *control_function(void *),void *controller){
    pthread_create(&(this->control_thread),NULL,control_function,controller);
    return true;
}

bool AutoControlSystem::stop_control(){
   pthread_cancel(this->control_thread);
   return true;
}

bool AutoControlSystem::check_system(){
    return (pthread_kill(this->control_thread, 0) != ESRCH);
}

void * AutoControlSystem::control_function(void *arg){
    return NULL;
}


