#ifndef OPENGLSCENEOBJECT_H
#define OPENGLSCENEOBJECT_H

#include "lib/cs123scenedata.h"
#include "glm/glm.hpp"
#include "gl/shaders/CS123Shader.h"
#include "shape/opengl/openglshape.h"
#include "shape/opengl/cube.h"
#include "shape/opengl/cone.h"
#include "shape/opengl/sphere.h"
#include "shape/opengl/cylinder.h"
#include "map"
#include "scene/boundingbox.h"

class SnowSceneObject
{
public:
    SnowSceneObject(glm::vec3 coords, float length, float width, float height);
    ~SnowSceneObject();

    virtual void render(std::unique_ptr<CS123Shader>  &shader, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    BoundingBox getBoundingBox();

    glm::vec3 getCoords();

protected:
    std::vector<CS123ScenePrimitive> m_primitives;
    std::vector<glm::mat4x4> m_transformations;

    glm::vec3 m_coords;
    float m_length;
    float m_width;
    float m_height;

    BoundingBox m_boundingBox;
};


#endif // OPENGLSCENEOBJECT_H
