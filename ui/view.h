#ifndef VIEW_H
#define VIEW_H

#include "GL/glew.h"
#include <qgl.h>
#include <QTime>
#include <QTimer>
#include "camera/camtranscamera.h"
#include "scene/openglscene.h"
#include "scene/snowscene/snowscene.h"

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

    void initScenes();
    void initCameras();

    void setScene(OpenGLScene *scene);
    void setCamera(Camera *camera);

    std::unique_ptr<SnowScene> m_snowScene;
    std::unique_ptr<CamtransCamera> m_camtransCamera;

    OpenGLScene *m_currentScene;
    Camera *m_currentCamera;

    glm::vec4      m_cameraEye;
    bool           m_isDragging;

    float m_lastTime;
    int m_nbFrames;

private slots:
    void tick();
};

#endif // VIEW_H
