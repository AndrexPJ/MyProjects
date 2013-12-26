#include "guielements.h"



HeightLevelWidget::HeightLevelWidget(double *controlled_height, double max_height, QWidget *parent) : QWidget(parent)
{
    this->current_height = controlled_height;
    this->max_height = max_height;
    this->required_height = 0;
}

HeightLevelWidget::~HeightLevelWidget()
{
}


void HeightLevelWidget::set_required_height(double height){
    this->required_height = height;
}

void HeightLevelWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QSize sz = this->size();
    painter.setPen(Qt::black);
    painter.drawRect(0,0,sz.width()-1,sz.height()-1);

    double dh = ((double)sz.height()) / this->max_height;
    double y = 0;

    // paint current height
    painter.setPen(Qt::green);
    painter.setBrush(Qt::green);
    y = (*this->current_height)*dh;
    painter.drawRect(1,sz.height()-2,sz.width()-3,-y);
    std::string sstr = (Tools::ToStrConverter<double>::convert((*this->current_height)));
    QString str = QString::fromStdString(sstr);
    painter.drawText(2,sz.height()-y-5,str);

    // paint required height
    painter.setPen(Qt::red);
    painter.brushOrigin();
    y = (this->required_height * dh);
    painter.drawRect(1,sz.height()-y-3,sz.width()-3,1);
    sstr = (Tools::ToStrConverter<double>::convert((this->required_height)));
    str = QString::fromStdString(sstr);
    painter.drawText(sz.width()-50,sz.height()-y-5,str);


}


HeadingAngleWidget::HeadingAngleWidget(double *controlled_heading_angle, double max_angle, QWidget *parent) : QWidget(parent){
    this->current_angle = controlled_heading_angle;
    this->max_angle = max_angle;
    this->required_angle = 0;
}

HeadingAngleWidget::~HeadingAngleWidget(){

}

void HeadingAngleWidget::set_required_angle(double angle){
    this->required_angle = angle;
}

void HeadingAngleWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QSize sz = this->size();
    double c_x,c_y;
    c_x = double(sz.width())/2;
    c_y = double(sz.height())/2;
    painter.setPen(Qt::black);
    painter.drawEllipse(0,0,sz.width()-1,sz.height()-1);
    painter.drawLine(c_x-10,c_y,c_x+10,c_y);
    painter.drawLine(c_x,c_y-10,c_x,c_y+10);


    painter.setPen(Qt::green);
    double angle = (-*(this->current_angle))*M_PI/180;
    painter.drawLine(c_x,c_y,(c_x)*(cos(angle)+1),(c_y)*(sin(angle)+1));
    std::string sstr = (Tools::ToStrConverter<double>::convert((*this->current_angle)));
    QString str = QString::fromStdString(sstr);
    painter.drawText(c_x + 20,c_y,str);

    painter.setPen(Qt::red);
    angle = (-(this->required_angle))*M_PI/180;
    painter.drawLine(c_x,c_y,(c_x)*(cos(angle)+1),(c_y)*(sin(angle)+1));
    sstr = (Tools::ToStrConverter<double>::convert((this->required_angle)));
    str = QString::fromStdString(sstr);
    painter.drawText(c_x + 20,c_y + 20,str);

}


StateButton::StateButton(QString name, QWidget *parent) : QWidget(parent){
    this->state = 0; //not active
    this->name = name;
}

StateButton::~StateButton(){
}

void StateButton::set_state(int state){
    this->state = state;
}

void StateButton::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QSize sz = this->size();
    painter.setPen(Qt::black);

    QString text = "";
    QBrush brush;
    switch (state) {
    case -1:
        text = "BROKEN";
        brush = Qt::red;
        break;
    case 0:
        text = "WAITING";
        brush = Qt::yellow;
        break;
    case 1:
        text = "RUNNING";
        brush = Qt::green;
        break;
    }

    painter.drawRect(0,0,sz.width()-1,sz.height()-1);
    painter.setBrush(brush);
    painter.drawRect(1,1,sz.width()-2,sz.height()-2);
    double c_y,c_x;
    c_x = double(sz.width())/2;
    c_y = double(sz.height())/2;

    painter.drawText(c_x/2,c_y,text);
    painter.drawText(c_x/2,c_y*2 - 10,this->name);

}

