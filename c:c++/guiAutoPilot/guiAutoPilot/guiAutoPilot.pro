#-------------------------------------------------
#
# Project created by QtCreator 2013-12-25T20:49:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = guiAutoPilot
TEMPLATE = app


SOURCES += main.cpp\
    AutoControlSystems/autocontrolsystem.cpp \
    AutoControlSystems/headingangleautocontrolsystem.cpp \
    AutoControlSystems/heightautocontrolsystem.cpp \
    AutoPilotSystems/autopilotsystem.cpp \
    ControlSystems/controlsystem.cpp \
    ControlSystems/headinganglecontrolsystem.cpp \
    ControlSystems/heightcontrolsystem.cpp \
    MeterSystems/headinganglemetersystem.cpp \
    MeterSystems/heightmetersystem.cpp \
    MeterSystems/metersystem.cpp \
    planecontrolsystem.cpp \
    autopilotgui.cpp \
    tools.cpp \
    guielements.cpp


HEADERS  += \
    AutoControlSystems/autocontrolsystem.h \
    AutoControlSystems/headingangleautocontrolsystem.h \
    AutoControlSystems/heightautocontrolsystem.h \
    AutoPilotSystems/autopilotsystem.h \
    ControlSystems/controlsystem.h \
    ControlSystems/headinganglecontrolsystem.h \
    ControlSystems/heightcontrolsystem.h \
    MeterSystems/headinganglemetersystem.h \
    MeterSystems/heightmetersystem.h \
    MeterSystems/metersystem.h \
    planecontrolsystem.h \
    autopilotgui.h \
    tools.h \
    guielements.h


FORMS    += mainwindow.ui
