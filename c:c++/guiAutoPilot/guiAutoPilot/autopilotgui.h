#ifndef AUTOPILOTGUI_H
#define AUTOPILOTGUI_H


#include "guielements.h"


class AutoPilotGUI
{

private:
    QWidget window;
    QGridLayout *layout, *button_layout;
    HeightLevelWidget *heightLevel;
    HeadingAngleWidget *hangleLevel;


    double required_height,required_angle;
public:
    StateButton *main_ap_b,*spare_ap_b;

    AutoPilotGUI(double *height,double *angle);
    void set_height(double height);
    void set_angle(double angle);
    void update();
    void show();
};





#endif // AUTOPILOTGUI_H
