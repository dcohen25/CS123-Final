#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H

#include "scene/scene.h"
#include "map"
#include "shape/opengl/openglshape.h"
#include "lib/cs123scenedata.h"
#include <string>

// Maximum number of lights, as defined in shader.
const int MAX_NUM_LIGHTS = 10;

class View;


/**
 * @class  OpenGLScene
 *
 * Basic Scene abstract class that supports OpenGL. Students will extend this class in ShapesScene
 * and SceneviewScene.
 */
class OpenGLScene : public Scene {
public:
    OpenGLScene();
    virtual ~OpenGLScene();
    virtual void render(View *context) = 0;
protected:
    void setClearColor();
    std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> m_shapes; // scene shapes
    void initShapes();
};

#endif // OPENGLSCENE_H
