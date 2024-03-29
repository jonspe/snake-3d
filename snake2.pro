#-------------------------------------------------
#
# Project created by QtCreator 2019-02-23T19:57:59
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
    main.cpp \
    snake.cpp \
    camera.cpp \
    resourcemanager.cpp \
    renderable.cpp \
    gamewindow.cpp \
    transform.cpp \
    gameobject.cpp \
    level.cpp \
    scene.cpp \
    fooditem.cpp \
    foodeffect.cpp \
    snakeproperties.cpp

HEADERS += \
    snake.hh \
    renderable.hh \
    camera.hh \
    resourcemanager.hh \
    gamewindow.hh \
    transform.hh \
    gameobject.hh \
    level.hh \
    scene.hh \
    fooditem.hh \
    foodeffect.hh \
    snakeproperties.hh

RESOURCES += \
    resource.qrc
