#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(AutoPilotGUI *gui,PlaneControlSystem *plane_c,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget((QWidget*)gui);

    this->plane_control = plane_c;
    this->gui = gui;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(){
    QMainWindow::update();
}
