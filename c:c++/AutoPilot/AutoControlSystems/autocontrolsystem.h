#ifndef AUTOCONTROLSYSTEM_H
#define AUTOCONTROLSYSTEM_H

#include <pthread.h>
#include <signal.h>
#include <iostream>
#include <unistd.h>
#include <cmath>

class AutoControlSystem
{
public:
    double accuracy;
    double controlled_parameter;
    pthread_t control_thread;

    AutoControlSystem(double controlled_parameter_start_value = 0);
    static void *control_function(void *controller);
    bool start_control(void * control_function(void*), void *controller);
    bool stop_control(void);
    bool check_system(void);
};

#endif // AUTOCONTROLSYSTEM_H
