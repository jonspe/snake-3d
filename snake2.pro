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
    main_window.cpp \
    gameobject.cpp \
    camera.cpp \
    gameobject.cpp \
    resourcemanager.cpp \
    renderable.cpp

HEADERS += \
    snake.hh \
    powerup.hh \
    renderable.hh \
    main_window.hh \
    gameobject.hh \
    camera.hh \
    resourcemanager.hh

DISTFILES += \
    shaders/snake_fragment.glsl \
    shaders/snake_vertex.glsl \
    shaders/snake_fragment.glsl \
    shaders/snake_vertex.glsl \
    textures/skybox/sky_bottom.tga \
    textures/skybox/sky_horizon.tga \
    textures/skybox/sky_top.tga
