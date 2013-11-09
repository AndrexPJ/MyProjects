#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGLWidget>
#include <QTimer>
#include <QtGui>
#include <QtGui/QMainWindow>
#include "Camera.h"

using namespace std;

class MainWindow : public QGLWidget
{
    Q_OBJECT
public:
    QTimer *keysTimer;
    Camera viewCam;
    MainWindow(QWidget *parent = 0);
private:
    int mouseOldX,mouseOldY;
    float angleX,angleY;
    float posX,posY,posZ;
    float rotationSpeed,posSpeed;
    list<int> keys;
protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();
    void mousePressEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
protected slots:
    void keysProc();
};

#endif // MAINWINDOW_H
