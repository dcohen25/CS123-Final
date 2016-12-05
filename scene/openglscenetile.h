#ifndef OPENGLSCENETILE_H
#define OPENGLSCENETILE_H

#include "glm/glm.hpp"
#include "gl/shaders/CS123Shader.h"
#include "openglsceneobject.h"

namespace CS123 { namespace GL {
class OpenGLSceneTile
{
public:
    OpenGLSceneTile(glm::vec3 coords, float tileSize);
    OpenGLSceneTile();
    ~OpenGLSceneTile();

    virtual void render(std::unique_ptr<CS123Shader> &shader);

    void setSize(float size);
    void setCoords(glm::vec3 coords);

    float getSize();
    glm::vec3 getCoords();

protected:
    glm::vec3 m_coords;
    float m_tileSize;

    std::vector<OpenGLSceneObject> m_sceneObjects;
};
}}
#endif // OPENGLSCENETILE_H
