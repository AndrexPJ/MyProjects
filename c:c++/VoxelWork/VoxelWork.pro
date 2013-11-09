#-------------------------------------------------
#
# Project created by QtCreator 2012-12-04T15:46:37
#
#-------------------------------------------------

QT       += core gui\
        opengl

TARGET = VoxelWork
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Voxel.cpp \
    specialFunctions.cpp \
    Camera.cpp \
    octTree.cpp

HEADERS  += mainwindow.h \
    Voxel.h \
    allHeaders.h \
    specialFunctions.h \
    Vector3D.h \
    Camera.h \
    octTree.h
