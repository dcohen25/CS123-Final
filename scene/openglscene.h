#ifndef OPENGLSCENE_H
#define OPENGLSCENE_H

#include "map"
#include "glm.hpp"
#include "gl/shaders/CS123Shader.h"
#include "lib/cs123scenedata.h"
#include "shape/opengl/openglshape.h"

// Maximum number of lights, as defined in shader.
const int MAX_NUM_LIGHTS = 10;

class View;


/**
 * @class  OpenGLScene
 *
 * Basic Scene abstract class that supports OpenGL. Students will extend this class in ShapesScene
 * and SceneviewScene.
 */
class OpenGLScene {
public:
    OpenGLScene();
    virtual ~OpenGLScene();

    virtual void render(View *context) = 0;
    virtual void updateScene(View *context) = 0;
protected:
    void setClearColor();
    void initShapes();

    std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> m_shapes;

};

#endif // OPENGLSCENE_H
