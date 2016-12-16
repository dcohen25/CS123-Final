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
#include "view.h"
#include "snowscenetextures.h"

class SnowSceneObject
{
public:
    SnowSceneObject(glm::vec3 coords, float length, float width, float height);
    ~SnowSceneObject();

    virtual void renderShadowScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) = 0;
    virtual void renderPhongScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) = 0;
    BoundingBox getBoundingBox();
    glm::vec3 getCoords();

protected:
    glm::vec3 m_coords;
    float m_length;
    float m_width;
    float m_height;
    BoundingBox m_boundingBox;
};


#endif // OPENGLSCENEOBJECT_H
