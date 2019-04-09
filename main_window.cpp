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

    x = .0f;
}

void MainWindow::toggleFullscreen()
{
    if (visibility() == Visibility::FullScreen)
        setVisibility(Visibility::Windowed);
    else
        setVisibility(Visibility::FullScreen);
}

void MainWindow::resizeGL(int width, int height) {}

void MainWindow::paintGL()
{
    // Clear previous image
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set projection to identity matrix
    glLoadIdentity();

    glRotatef(x, 0.0f, 0.0f, 1.0f);

    // Draw calls here
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(.0f, .5f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(.5f, -.5f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-.5f, -.5f, 0.0f);

    glEnd();

    // Empty buffers
    glFlush();

    x += 1.0f;
    qDebug() << x;
}

// Empty for now
void MainWindow::initializeGL() {
    initializeOpenGLFunctions();
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
    default:
        break;
    }

}
