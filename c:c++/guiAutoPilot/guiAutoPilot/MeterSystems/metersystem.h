#ifndef METERSYSTEM_H
#define METERSYSTEM_H

class MeterSystem
{
public:
    MeterSystem();
    virtual double get_value(void) = 0;
};

#endif // METERSYSTEM_H
