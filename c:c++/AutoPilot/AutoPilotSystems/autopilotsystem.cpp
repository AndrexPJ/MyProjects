#include "autopilotsystem.h"

AutoPilotSystem::AutoPilotSystem(HeightAutoControlSystem *heightACS, HeadingAngleAutoControlSystem *headingAngleACS){
    this->headingAngleACS = headingAngleACS;
    this->heightACS = heightACS;
}
