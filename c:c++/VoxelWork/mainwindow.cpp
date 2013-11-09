#include "mainwindow.h"
#include <allHeaders.h>



MainWindow::MainWindow(QWidget* parent) : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer));
    this->angleY = 0;
    this->angleX = 0;
    this->mouseOldX = 0;
    this->mouseOldY = 0;
    this->rotationSpeed = 0.1;
    keysTimer = new QTimer(this);
    connect(keysTimer, SIGNAL(timeout()), this, SLOT(keysProc()));
}

void MainWindow::initializeGL()
{
   qglClearColor(Qt::white);
   glEnable(GL_LIGHTING);
   glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
   glEnable(GL_NORMALIZE);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_COLOR_MATERIAL);
}

void MainWindow::resizeGL(int nWidth, int nHeight)
{
    //glViewport(0,0,(GLint)nWidth,(GLint)nHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0f,(GLfloat)this->width()/(GLfloat)this->height(),1.0f,800.0f);
    viewCam.LookAt(this->angleX,this->angleY);
    viewCam.Update();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.0,0.9,0.1);
    glBegin(GL_QUADS);
    glNormal3f(0.0,1.0,0.0);
        glVertex3f(-900.0,0.0,-900.0);
        glVertex3f(900.0,0.0,-900.0);
        glVertex3f(900.0,0.0,900.0);
        glVertex3f(-900.0,0.0,900.0);
    glEnd();

    //GLUquadricObj *qObj = gluNewQuadric();
    float light_position[] = {10.0,400.0,1.0,1.0};
    float Ambient[] = {0.0,0.0,0.0,1.0};
    float Diffuse[] = {1.0,1.0,1.0,1.0};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv( GL_LIGHT0, GL_AMBIENT, Ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, Diffuse );

    glVoxelBegin();
    for(float x = 0;x<50;x+=2)
    {
        for(float y = 1 ; y < 50;y+=2)
        {
            for(float z = 0 ; z < 50;z+=2){
                glColor3f((float)z/50,(float)y/50,(float)x/50 ) ;
                glVoxelFull(x,y,z,0.5);
            }
        }

    }

    glVoxelEnd();

    glDisable(GL_LIGHT0);
    std::cout <<"x: " << viewCam.eye.x << " y: " << viewCam.eye.y <<" z: "<<viewCam.eye.z<<std::endl;

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    this->mouseOldX = e->x();
    this->mouseOldY = e->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{

    this->angleX = this->angleX + (float)(e->x() - this->mouseOldX) * rotationSpeed;
    this->angleY = this->angleY + (float)(e->y() - this->mouseOldY) * rotationSpeed;
    this->mouseOldX = e->x();
    this->mouseOldY = e->y();
    updateGL();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
        case Qt::Key_W :
        {
        if(!listElem((int)Qt::Key_W,this->keys))
            {
                this->keys.push_back((int)Qt::Key_W);
            }
            break;
        }
        case Qt::Key_S :
        {
        if(!listElem((int)Qt::Key_S,this->keys))
            {
                this->keys.push_back((int)Qt::Key_S);
            }
            break;
        }
        case Qt::Key_A :
        {
        if(!listElem((int)Qt::Key_A,this->keys))
            {
                this->keys.push_back((int)Qt::Key_A);
            }
            break;
        }
        case Qt::Key_D :
        {
        if(!listElem((int)Qt::Key_D,this->keys))
            {
                this->keys.push_back(Qt::Key_D);
            }
            break;
        }
        case Qt::Key_Space :
        {
        if(!listElem((int)Qt::Key_Space,this->keys))
            {
                this->keys.push_back((int)Qt::Key_Space);

            }
            break;
        }

        case Qt::Key_Z:
        {
        if(!listElem((int)Qt::Key_Z,this->keys))
            {
                this->keys.push_back((int)Qt::Key_Z);
            }
            break;
        }
        default :
        {
        return;
        }

    }
    keysTimer->start(30);

}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    this->keys.remove(e->key());
    if(this->keys.empty()) keysTimer->stop();
}

void MainWindow::keysProc(void)
{
    for(list<int>::iterator it = this->keys.begin();it!=this->keys.end();it++)
    {
        switch(*it)
        {
        case Qt::Key_W :
        {
            viewCam.MoveF();
            break;
        }
        case Qt::Key_S :
        {
            viewCam.MoveB();
            break;
        }
        case Qt::Key_A :
        {
            viewCam.MoveL();
            break;
        }
        case Qt::Key_D :
        {
            viewCam.MoveR();
            break;
        }
        case Qt::Key_Space :
        {
            viewCam.MoveUp();
            break;
        }

        case Qt::Key_Z:
        {
            viewCam.MoveDown();
            break;
        }

        }
    }
    updateGL();
}
