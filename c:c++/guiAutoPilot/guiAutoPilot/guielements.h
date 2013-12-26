#ifndef GUIELEMENTS_H
#define GUIELEMENTS_H

#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>

#include <cmath>
#include <string>
#include "tools.h"

class HeightLevelWidget : public QWidget
{
    Q_OBJECT

public:
    HeightLevelWidget(double *controlled_height,double max_height = 10000,QWidget *parent = 0);
    void set_required_height(double height);
    ~HeightLevelWidget();

public slots:
    void set_height(int height);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    double required_height, *current_height, max_height;

};

class HeadingAngleWidget : public QWidget
{
    Q_OBJECT

public:
    HeadingAngleWidget(double *controlled_heading_angle,double max_angle = 360,QWidget *parent = 0);
     ~HeadingAngleWidget();
    void set_required_angle(double angle);

public slots:
    void set_angle(int angle);
protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    double required_angle, *current_angle, max_angle;

};

class StateButton : public QWidget
{
    Q_OBJECT

public:
    StateButton(QString name = "Button",QWidget *parent = 0);
     ~StateButton();
    void set_state(int state);


protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QString name;
    int state;

};




#endif // GUIELEMENTS_H
