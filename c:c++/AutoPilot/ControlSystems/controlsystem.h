#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

class ControlSystem
{
public:
    ControlSystem();
    virtual void set_value(double value) = 0;
};

#endif // CONTROLSYSTEM_H
