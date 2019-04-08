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
# File: main_window.hh                                             #
# Description: Declares a class implementing a UI for the game.    #
#                                                                  #
# Author: First Last, student#, first.last@tuni.fi                 #
####################################################################
*/

#ifndef PRG2_SNAKE2_MAINWINDOW_HH
#define PRG2_SNAKE2_MAINWINDOW_HH

#include <QOpenGLWindow>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>
#include <QDebug>

#include <random>


const QSize DEFAULT_SIZE(1280, 720);
const QSize MIN_SIZE(640, 480);


class MainWindow: public QOpenGLWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override = default;

    void keyPressEvent(QKeyEvent* event) override;

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL() override;

private slots:
    // Maybe not anything here?

private:
    std::default_random_engine rng_;    /**< Randomizes food locations. */
    void toggleFullscreen();

};


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
