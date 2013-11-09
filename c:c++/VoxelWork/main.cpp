#include <QtGui/QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle("VoxelWork");
    window.setGeometry(100,100,1024,1024);
    window.show();
    return app.exec();
}
