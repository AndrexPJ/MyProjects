#include "autopilotgui.h"

AutoPilotGUI::AutoPilotGUI(double *height, double *angle){

    this->layout = new QGridLayout;
    this->button_layout = new QGridLayout;

    this->heightLevel = new HeightLevelWidget(height);
    this->hangleLevel = new HeadingAngleWidget(angle);

    this->required_angle = 0.0;
    this->required_height = 0.0;

    this->main_ap_b = new StateButton("Main AP");
    this->spare_ap_b = new StateButton("Spare AP");

    this->button_layout->addWidget(main_ap_b,0,0);
    this->button_layout->addWidget(spare_ap_b,0,1);

    this->layout->addWidget(this->heightLevel,0,0);
    this->layout->addWidget(this->hangleLevel,0,1);
    this->layout->addLayout(button_layout,0,2);

    this->window.setLayout(this->layout);


}

AutoPilotGUI::~AutoPilotGUI(){
    this->window.close();
}

void AutoPilotGUI::show(){
    this->window.show();
}


void AutoPilotGUI::set_angle(double angle){
    this->required_angle = angle;
    this->hangleLevel->set_required_angle(angle);
}

void AutoPilotGUI::set_height(double height){
    this->required_height = height;
    this->heightLevel->set_required_height(height);
}

void AutoPilotGUI::update(){
    this->window.update();
}


