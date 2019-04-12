/**
  TIE-02201 Ohjelmointi 2: Perusteet, K2019
  Assignment 12.4: Matopelin paluu
    3D Snake game made with OpenGL 2.1 immediate mode.
    See 'instructions.txt' for further information.

  main_window.cpp
    Defines a class implementing a UI for the game.

  @author Joona Perasto, 272725, joona.perasto@tuni.fi
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
    snake_ = new Snake(3.4f, 0.7f, 4.0f);
    snake_->steer(1);

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
    qint64 ns = elapsed_timer_.nsecsElapsed();
    float time_delta = float(ns-prev_ns_) * 1.0f/1000000000.0f;
    prev_ns_ = ns;

    snake_->update(time_delta);
    gameRender();
}

void MainWindow::gameRender()
{
    // Clear previous image
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl->glClearColor(0.5f, 0.75f, 0.95f, 0.0f);

    // Set projection to identity matrix
    gl->glLoadIdentity();

    rot = -snake_->getHeading() / 3.1415f * 180.0f + 90.0f;
    camera_pos = QVector3D(0.0f, 0.0f, -2.1f);

    // Calculate camera matrix
    QMatrix4x4 mat;
    float aspect = float(width()) / float(height());
    mat.perspective(60.0f, aspect, 0.01f, 7.0f);
    mat.translate(camera_pos);
    mat.rotate(50.0f, QVector3D(-1.0f, 0.0f, 0.0f));
    mat.rotate(rot, QVector3D(0.0, 0.0f, 1.0f));
    mat.translate(-snake_->getPosition());

    // Apply camera matrix
    gl->glMultMatrixf(mat.constData());

    // Draw play area
    gl->glColor3f(0.4f, 1.0f, 0.25f);
    gl->glBegin(GL_QUADS);
    gl->glVertex3f(-1.0f, 1.0f, -0.02f);
    gl->glVertex3f(1.0f, 1.0f, -0.02f);
    gl->glVertex3f(1.0f, -1.0f, -0.02f);
    gl->glVertex3f(-1.0f, -1.0f, -0.02f);
    gl->glEnd();

    // Draw snake
    gl->glColor3f(0.0f, 0.3f, 0.1f);
    snake_->render(gl);

    // Empty buffers
    gl->glFlush();

    // Window requires updating to show rendered result
    update();
}

void MainWindow::initializeGL() {
    gl = new QOpenGLFunctions_2_1;
    gl->initializeOpenGLFunctions();

    gl->glEnable(GL_MULTISAMPLE);
    gl->glEnable(GL_DEPTH_TEST);

    camera_pos = QVector3D(0.0f, 0.0f, -2.1f);

    timer_.setInterval(16);
    timer_.start();

    prev_ns_ = 0;
    elapsed_timer_.start();
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
    // Ignore repeated keys
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
