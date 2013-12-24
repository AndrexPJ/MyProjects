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
    HeightAutoControlSystem *heightACS;
    HeadingAngleAutoControlSystem *headingAngleACS;
public:
    AutoPilotSystem(HeightAutoControlSystem *heightACS, HeadingAngleAutoControlSystem *headingAngleACS);
};



#endif // AUTOPILOTSYSTEM_H
