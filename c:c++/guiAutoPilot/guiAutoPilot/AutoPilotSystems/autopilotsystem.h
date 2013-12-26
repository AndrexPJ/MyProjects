#ifndef AUTOPILOTSYSTEM_H
#define AUTOPILOTSYSTEM_H

#include "AutoControlSystems/heightautocontrolsystem.h"
#include "MeterSystems/heightmetersystem.h"
#include "ControlSystems/heightcontrolsystem.h"

#include "AutoControlSystems/headingangleautocontrolsystem.h"
#include "MeterSystems/headinganglemetersystem.h"
#include "ControlSystems/headinganglecontrolsystem.h"


class AutoPilotSystem
{
private:
    pthread_t *heigthCS_thread, *headingAngleCS_thread;
    HeightAutoControlSystem *heightACS;
    HeadingAngleAutoControlSystem *headingAngleACS;
public:
    AutoPilotSystem();
    AutoPilotSystem(HeightAutoControlSystem *heightACS, HeadingAngleAutoControlSystem *headingAngleACS);
    ~AutoPilotSystem();
    bool set_height(double height);
    bool set_heading_angle(double heading_angle);
    bool check_system(void);
    bool start_control(void);
    bool stop_control(void);
};


class AutoPilotSystemFactory{
public:
    static AutoPilotSystem build_system(double *controlled_height, double start_height,
                                        double *controlled_heading_angle, double start_heding_angle,
                                        double height_change_rate = 0.03, double heading_angle_change_rate = 0.05
                                        );
};


#endif // AUTOPILOTSYSTEM_H
