#ifndef PLANECONTROLSYSTEM_H
#define PLANECONTROLSYSTEM_H

#include <pthread.h>
#include "AutoPilotSystems/autopilotsystem.h"


class PlaneControlSystem
{
private:
    double *plane_height, *plane_heading_angle;
    double required_height, required_heading_angle;
    bool main_autopilot_state;

    AutoPilotSystem *main_autopilot;
    AutoPilotSystem *spare_autopilot;

    pthread_t control_thread;

public:

    PlaneControlSystem(AutoPilotSystem *main_autopilot, AutoPilotSystem *spare_autopilot,
                       double *controlled_height, double *controlled_heading_angle);

    static void *control_function(void *controller);
    bool start_control(void);
    bool stop_control(void);

    void set_height(double height);
    void set_heading_angle(double heading_angle);

    double get_height(void);
    double get_heading_angle(void);

    bool get_main_autopilot_state(void);
    bool get_spare_autopilot_state(void);

    void kill_main_autopilot(void);


};



#endif // PLANECONTROLSYSTEM_H
