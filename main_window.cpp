/*
####################################################################
# TIE-02201 Ohjelmointi 2: Perusteet, K2019                        #
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project4: Snake: The Revengeance                                 #
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: main_window.cpp                                            #
# Description: Defines a class implementing a UI for the game.     #
#                                                                  #
# Author: First Last, student#, first.last@tuni.fi                 #
####################################################################
*/

#include "main_window.hh"

MainWindow::MainWindow() {

    // Window settings
    setTitle("Snakey Boi");
    resize(DEFAULT_SIZE);
    setMinimumSize(MIN_SIZE);

    // Set OpenGL compatibility
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2, 1);
    setFormat(format);

    // Game init
    snake_ = new Snake(1.4f, 0.7f, 5.0f);

    connect(&timer_, &QTimer::timeout, this, &MainWindow::gameUpdate);
}

void MainWindow::toggleFullscreen()
{
    if (visibility() == Visibility::FullScreen)
        setVisibility(Visibility::Windowed);
    else
        setVisibility(Visibility::FullScreen);
}

void MainWindow::gameUpdate()
{
    float time_delta = 0.016f;
    snake_->update(time_delta);

    gameRender();
}

void MainWindow::gameRender()
{
    // Clear previous image
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set projection to identity matrix
    gl->glLoadIdentity();

    // Draw calls here
    snake_->render(gl);

    // Empty buffers
    gl->glFlush();


    update();
}

void MainWindow::paintGL()
{
    // Clear previous image
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set projection to identity matrix
    gl->glLoadIdentity();

    // Draw calls here
    snake_->render(gl);

    // Empty buffers
    gl->glFlush();
}

// Empty for now
void MainWindow::initializeGL() {
    gl = new QOpenGLFunctions_2_1;
    gl->initializeOpenGLFunctions();

    timer_.setInterval(15);
    timer_.start();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // Ignore repeated keys
    if (event->isAutoRepeat()) return;
    qDebug() << event->key();

    switch(event->key()) {
    case Qt::Key_F11:
        toggleFullscreen();
        break;
    case Qt::Key_A:
        snake_->steer(1);
        break;
    case Qt::Key_D:
        snake_->steer(-1);
        break;

    default:
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;

    switch(event->key()) {
    case Qt::Key_A:
        snake_->steer(0);
        break;
    case Qt::Key_D:
        snake_->steer(0);
        break;

    default:
        break;
    }
}
