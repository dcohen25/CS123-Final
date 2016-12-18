#ifndef VIEW_H
#define VIEW_H

#include "GL/glew.h"
#include <qgl.h>
#include <QTime>
#include <QTimer>
#include "camera/camera.h"
#include "scene/openglscene.h"

#include "gl/datatype/FBO.h"

class View : public QGLWidget
{
    Q_OBJECT

public:
    View(QWidget *parent);
    ~View();

    Camera *getCamera();
    OpenGLScene *getScene();
    void resizeGL(int w, int h);

private:
    QTime m_time;
    QTimer m_timer;
    bool m_captureMouse;

    void initializeGL() override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    std::unique_ptr<OpenGLScene> m_currentScene;
    std::unique_ptr<Camera> m_currentCamera;

    glm::vec4      m_cameraEye;
    bool           m_isDragging;

    float m_lastTime;
    int m_nbFrames;

    // particles
    void drawParticles();
    void setParticleViewport();

    int m_width;
    int m_height;

    GLuint m_particleUpdateProgram;
    GLuint m_particleDrawProgram;

    std::unique_ptr<OpenGLShape> m_quad;

    GLuint m_particlesVAO;
    std::shared_ptr<FBO> m_particlesFBO1;
    std::shared_ptr<FBO> m_particlesFBO2;
    bool m_firstPass;
    bool m_evenPass;
    int m_numParticles;

private slots:
    void tick();
};

#endif // VIEW_H
