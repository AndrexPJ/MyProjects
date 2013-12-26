#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(AutoPilotSystem *main_autopilot, AutoPilotSystem *spare_autopilot, double *height,double *angle, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedHeight(500);
    this->setFixedWidth(900);
    this->main_autopilot = main_autopilot;
    this->spare_autopilot = spare_autopilot;
    this->main_ap_state = 0;
    this->spare_ap_state = 0;

    this->height = height;
    this->angle = angle;
    this->started = false;
    this->random_state = false;

    this->plane_control = new PlaneControlSystem(main_autopilot,spare_autopilot,height,angle);

    HeightLevelWidget *h_level = new HeightLevelWidget(height);
    HeadingAngleWidget *a_level = new HeadingAngleWidget(angle);


    main_ap_b = new StateButton("Main AP");
    spare_ap_b = new StateButton("Spare AP");

    QWidget *main_w = new QWidget;
    QGridLayout *layout = new QGridLayout;
    QGridLayout *state_layout = new QGridLayout;

    state_layout->addWidget((QWidget*)main_ap_b,0,0);
    state_layout->addWidget((QWidget*)spare_ap_b,0,1);


    layout->addLayout(state_layout,0,2);
    layout->addWidget((QWidget*)h_level,0,0);
    layout->addWidget((QWidget*)a_level,0,1);

    QSlider *height_slider = new QSlider(Qt::Horizontal);
    QSlider *angle_slider = new QSlider(Qt::Horizontal);

    QGridLayout *height_control_l = new QGridLayout;
    QGridLayout *angle_control_l = new QGridLayout;
    QGridLayout *ap_control_l = new QGridLayout;

    layout->addLayout(height_control_l,1,0);
    layout->addLayout(angle_control_l,1,1);
    layout->addLayout(ap_control_l,1,2);

    QPushButton *start_button = new QPushButton("Start");
    connect(start_button, SIGNAL(clicked()),this, SLOT(start()));
    QPushButton *stop_button = new QPushButton("Stop");
    connect(stop_button, SIGNAL(clicked()),this, SLOT(stop()));

    QPushButton *random_button = new QPushButton("Random");
    connect(random_button, SIGNAL(clicked()),this, SLOT(random_start_stop()));

    QPushButton *kill_button = new QPushButton("Kill");
    connect(kill_button, SIGNAL(clicked()),this, SLOT(kill_main_ap()));

    QPushButton *reset_button = new QPushButton("Reset");
    connect(reset_button,SIGNAL(clicked()),this,SLOT(reset_system()));

    height_control_l->addWidget((QWidget*)height_slider,0,0);
    height_slider->setMaximum(9000);
    connect(height_slider, SIGNAL(valueChanged(int)),h_level, SLOT(set_height(int)));
    connect(height_slider, SIGNAL(valueChanged(int)),this, SLOT(set_height(int)));

    angle_control_l->addWidget((QWidget*)angle_slider,0,0);
    angle_slider->setMaximum(360);
    connect(angle_slider, SIGNAL(valueChanged(int)),a_level, SLOT(set_angle(int)));
    connect(angle_slider, SIGNAL(valueChanged(int)),this, SLOT(set_angle(int)));

    ap_control_l->addWidget((QWidget*)start_button,1,0);
    ap_control_l->addWidget((QWidget*)stop_button,1,1);
    ap_control_l->addWidget((QWidget*)kill_button,0,0);
    ap_control_l->addWidget((QWidget*)random_button,0,1);
    ap_control_l->addWidget((QWidget*)reset_button,2,0);

    QLabel *h_label = new QLabel("Height value");
    QLabel *a_label = new QLabel("Angle value");


    height_control_l->addWidget((QWidget*)h_label,1,0,Qt::AlignCenter);
    angle_control_l->addWidget((QWidget*)a_label,1,0,Qt::AlignCenter);

    main_w->setLayout(layout);

    this->setCentralWidget(main_w);

    QTimer *timer_random = new QTimer;
    connect(timer_random, SIGNAL(timeout()), this, SLOT(random()));
    timer_random->start(100);

    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(40);

}



MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::update(){

    if(this->plane_control->get_spare_autopilot_state()){
        this->spare_ap_state = 1;
        this->spare_ap_b->set_state(1);
    }
    QMainWindow::update();
}

void MainWindow::set_height(int height){
    this->plane_control->set_height(double(height));
}

void MainWindow::set_angle(int angle){
    this->plane_control->set_heading_angle(double(angle));
}

void MainWindow::start(){

    if(!this->started){
        if(this->main_ap_state != -1){
         this->main_ap_state = 1;
         this->main_ap_b->set_state(1);
         this->plane_control->start_control();
        }
        else{
            if(this->spare_ap_state != -1){
             this->spare_ap_state = 1;
             this->spare_ap_b->set_state(1);
             this->plane_control->start_spare_control();
            }
        }
        this->started = true;

    }
}

void MainWindow::stop(){
    if(this->main_ap_state != -1){
     this->main_ap_state = 0;
     this->main_ap_b->set_state(0);
    }
    else{
        if(this->spare_ap_state != -1){
         this->spare_ap_state = 0;
         this->spare_ap_b->set_state(0);
        }
    }
    if(this->started){
        this->started = false;
        this->plane_control->stop_control();
    }

}

void MainWindow::kill_main_ap(){
    this->main_ap_state = -1;
    this->plane_control->kill_main_autopilot();
    this->main_ap_b->set_state(-1);
    //this->spare_ap_state = 1;
    //this->spare_ap_b->set_state(1);
}

void MainWindow::random(){
    if(random_state){
       double r = double(qrand() % 20 - 10);
       *(this->height) += r;
       r = double(qrand() % 3 - 1);
       *(this->angle) += r;
    }
}

void MainWindow::random_start_stop(){
    this->random_state = !this->random_state;
}

void MainWindow::reset_system(){
    this->stop();
    this->main_ap_b->set_state(0);
    this->main_ap_state = 0;
    this->spare_ap_b->set_state(0);
    this->spare_ap_state = 0;
}
