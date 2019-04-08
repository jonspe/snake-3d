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

#include <QGraphicsRectItem>
#include <QKeyEvent>


MainWindow::MainWindow() {
    setTitle("Snakey Boi");

    resize(DEFAULT_SIZE);
    setMinimumSize(MIN_SIZE);

    setSurfaceType(QWindow::OpenGLSurface);
}

void MainWindow::toggleFullscreen()
{
    if (visibility() == Visibility::FullScreen)
        setVisibility(Visibility::Windowed);
    else
        setVisibility(Visibility::FullScreen);
}

void MainWindow::resizeGL(int width, int height)
{

}

void MainWindow::paintGL()
{
    // Clear previous image
    glClear(GL_COLOR_BUFFER_BIT);


}

void MainWindow::initializeGL()
{

}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) return;
    qDebug() << event->key();

    if (event->key() == Qt::Key_F11)
        toggleFullscreen();
}
