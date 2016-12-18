#include "view.h"

#include "viewformat.h"
#include <QApplication>
#include <QKeyEvent>
#include <iostream>
#include "scene/snowscene/snowscene.h"
#include "camera/camtranscamera.h"

#include "lib/resourceloader.h"
#include "gl/textures/Texture2D.h"
#include "gl/shaders/ShaderAttribLocations.h"


View::View(QWidget *parent) : QGLWidget(ViewFormat(), parent),
    m_time(), m_timer(), m_captureMouse(true),
    m_width(width()), m_height(height()),
    m_quad(nullptr), m_particlesFBO1(nullptr), m_particlesFBO2(nullptr),
    m_firstPass(true), m_evenPass(true), m_numParticles(3000)
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
    m_lastTime = 0;
    m_nbFrames = 0;
}

View::~View()
{
    glDeleteVertexArrays(1, &m_particlesVAO);
}

Camera *View::getCamera(){
    return m_currentCamera.get();
}

OpenGLScene *View::getScene(){
    return m_currentScene.get();
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
    m_timer.start(10);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    m_currentCamera = std::make_unique<CamtransCamera>();
    m_currentScene = std::make_unique<SnowScene>();

    // particle stuff
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

    m_particleUpdateProgram = ResourceLoader::createShaderProgram(
                ":/shaders/shaders/particles/quad.vert", ":/shaders/shaders/particles/particles_update.frag");
    m_particleDrawProgram = ResourceLoader::createShaderProgram(
                ":/shaders/shaders/particles/particles_draw.vert", ":/shaders/shaders/particles/particles_draw.frag");

    std::vector<GLfloat> quadData = {-1, 1, 0,
                                     0, 0,
                                     -1, -1, 0,
                                     0, 1,
                                     1, 1, 0,
                                     1, 0,
                                     1, -1, 0,
                                     1, 1};
    m_quad = std::make_unique<OpenGLShape>();
    m_quad->setVertexData(&quadData[0], quadData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, 4);
    m_quad->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->setAttribute(ShaderAttrib::TEXCOORD0, 2, 3*sizeof(GLfloat), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->buildVAO();

    glGenVertexArrays(1, &m_particlesVAO);
    // TODO [Task 12] Create m_particlesFBO1 and 2 with std::make_shared
    m_particlesFBO1 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1,
                                           TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE,
                                           TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
    m_particlesFBO2 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1,
                                           TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE,
                                           TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);

    GLint maxRenderBufferSize;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_EXT, &maxRenderBufferSize);
    std::cout << "Max FBO size: " << maxRenderBufferSize << std::endl;
}

void View::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO: Implement the demo rendering here
    m_currentCamera->setAspectRatio(static_cast<float>(width()) / static_cast<float>(height()));
    m_currentScene->render(this);

    // particles
    drawParticles();
    update();
}

void View::drawParticles() {
    auto prevFBO = m_evenPass ? m_particlesFBO1 : m_particlesFBO2;
    auto nextFBO = m_evenPass ? m_particlesFBO2 : m_particlesFBO1;
    float firstPass = m_firstPass ? 1.0f : 0.0f;

    // TODO [Task 13] Move the particles from prevFBO to nextFBO while updating them
    nextFBO->bind();
    glUseProgram(m_particleUpdateProgram);
    glActiveTexture(GL_TEXTURE0);
    prevFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    prevFBO->getColorAttachment(1).bind();

    glUniform1f(glGetUniformLocation(m_particleUpdateProgram, "firstPass"), firstPass);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "numParticles"), m_numParticles);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "prevPos"), 0);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "prevVel"), 1);

    m_quad->draw();

    // TODO [Task 16] Draw the particles from nextFBO
    nextFBO->unbind();
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_particleDrawProgram);
    setParticleViewport();

    glActiveTexture(GL_TEXTURE0);
    nextFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    nextFBO->getColorAttachment(1).bind();

    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "pos"), 0);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "vel"), 1);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "numParticles"), m_numParticles);

    glBindVertexArray(m_particlesVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3 * m_numParticles);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);

    m_firstPass = false;
    m_evenPass = !m_evenPass;

    glUseProgram(0);
}

void View::setParticleViewport() {
    int maxDim = std::max(m_width, m_height);
    int x = (m_width - maxDim) / 2.0f;
    int y = (m_height - maxDim) / 2.0f;
    glViewport(x, y, maxDim, maxDim);
}

void View::resizeGL(int w, int h)
{
    // for particles??
    m_width = w;
    m_height = h;

    float ratio = static_cast<QGuiApplication *>(QCoreApplication::instance())->devicePixelRatio();
    w = static_cast<int>(w / ratio);
    h = static_cast<int>(h / ratio);
//    glViewport(0, 0, w, h);
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
