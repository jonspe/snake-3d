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


MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent) {

    ui_.setupUi(this);
    ui_.graphicsView->setScene(&scene_);

    connect(&timer_, &QTimer::timeout, this, &MainWindow::moveSnake);
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    // TODO: Read the event to see which key got pressed and store the result.
    // You can remove this function if you don't need it.
}

void MainWindow::on_playButton_clicked() {
    // EXAMPLE: How to create new graphics items in the scene.
    const QRectF food_rect(0, 0, 1, 1);
    const QPen pen(Qt::white, 0);
    const QBrush brush(Qt::black);
    food_ = scene_.addRect(food_rect, pen, brush);
    food_->setPos(9, 5);

    adjustSceneArea();
    timer_.start(1000);
}

void MainWindow::moveSnake() {
    // EXAMPLE: How to move a graphics item left in the scene.
    const QPointF old_food_pos = food_->scenePos();
    const QPointF new_food_pos = old_food_pos + QPoint(-1, 0);
    food_->setPos(new_food_pos);
}

void MainWindow::adjustSceneArea() {
    // TODO: Replace the area's size with the play field's actual size.
    const QRectF area(0, 0, 10, 10);
    scene_.setSceneRect(area);
    ui_.graphicsView->fitInView(area);
}
