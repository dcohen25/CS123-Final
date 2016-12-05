#include "view.h"

#include "viewformat.h"
#include <QApplication>
#include <QKeyEvent>
#include <iostream>


View::View(QWidget *parent) : QGLWidget(ViewFormat(), parent),
    m_time(), m_timer(), m_captureMouse(true)
{
    // View needs all mouse move events, not just mouse drag events
    setMouseTracking(true);

    // Hide the cursor
    if(m_captureMouse) {
        QApplication::setOverrideCursor(Qt::BlankCursor);
    }

    // View needs keyboard focus
    setFocusPolicy(Qt::StrongFocus);

    // The update loop is implemented using a timer
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(tick()));
}

View::~View()
{
}

Camera *View::getCamera(){
    return m_currentCamera;
}

OpenGLScene *View::getScene(){
    return m_currentScene;
}

void View::initializeGL()
{
    // All OpenGL initialization *MUST* be done during or after this
    // method. Before this method is called, there is no active OpenGL
    // context and all OpenGL calls have no effect.

    //initialize glew
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if ( GLEW_OK != err ) {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cerr << "Something is very wrong, glew initialization failed." << std::endl;
    }
    std::cout << "Using GLEW " <<  glewGetString( GLEW_VERSION ) << std::endl;

    // Start a timer that will try to get 60 frames per second (the actual
    // frame rate depends on the operating system and other running programs)
    m_time.start();
    m_timer.start(1000 / 60);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    initScenes();
    initCameras();
    setCamera(m_camtransCamera.get());
    setScene(m_snowScene.get());
}

void View::initScenes() {
    m_snowScene = std::make_unique<SnowScene>();
}

void View::initCameras() {
    m_camtransCamera = std::make_unique<CamtransCamera>();
}

void View::setScene(OpenGLScene *scene){
    m_currentScene = scene;
}

void View::setCamera(Camera *camera){
    m_currentCamera = camera;
}

void View::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO: Implement the demo rendering here
    m_currentCamera->setAspectRatio(static_cast<float>(width()) / static_cast<float>(height()));
    m_currentScene->render(this);
}

void View::resizeGL(int w, int h)
{
    float ratio = static_cast<QGuiApplication *>(QCoreApplication::instance())->devicePixelRatio();
    w = static_cast<int>(w / ratio);
    h = static_cast<int>(h / ratio);
    glViewport(0, 0, w, h);
}

void View::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        m_currentCamera->mouseDown(event->x(), event->y());
        m_isDragging = true;
        update();
    }
}

void View::mouseMoveEvent(QMouseEvent *event)
{

    // This starter code implements mouse capture, which gives the change in
    // mouse position since the last mouse movement. The mouse needs to be
    // recentered after every movement because it might otherwise run into
    // the edge of the screen, which would stop the user from moving further
    // in that direction. Note that it is important to check that deltaX and
    // deltaY are not zero before recentering the mouse, otherwise there will
    // be an infinite loop of mouse move events.
    if(m_captureMouse) {

        int deltaX = event->x() - width() / 2;
        int deltaY = event->y() - height() / 2;
        if (!deltaX && !deltaY) return;
        QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));

        // TODO: Handle mouse movements here
        if (m_isDragging) {
            m_currentCamera->mouseDragged(deltaX, deltaY);
            update();
        }
    }
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isDragging && event->button() == Qt::RightButton) {
        m_currentCamera->mouseUp(event->x(), event->y());
        m_isDragging = false;
        update();
    }
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) QApplication::quit();

    // TODO: Handle keyboard presses here
    if (event->key() == Qt::Key_Down){
        m_currentCamera->keyDown();
        update();
    }
    else if (event->key() == Qt::Key_Up){
        m_currentCamera->keyUp();
        update();
    }
    else if (event->key() == Qt::Key_Left){
        m_currentCamera->keyLeft();
        update();
    }
    else if (event->key() == Qt::Key_Right){
        m_currentCamera->keyRight();
        update();
    }
}

void View::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Down ||
        event->key() == Qt::Key_Up ||
        event->key() == Qt::Key_Left ||
        event->key() == Qt::Key_Right){
        m_currentCamera->keyReleased();
        update();
    }
}

void View::tick()
{
    // Get the number of seconds since the last tick (variable update rate)
    float seconds = m_time.restart() * 0.001f;

    // TODO: Implement the demo update here
    m_currentScene->updateScene(this);
    // Flag this view for repainting (Qt will call paintGL() soon after)
    update();
}
