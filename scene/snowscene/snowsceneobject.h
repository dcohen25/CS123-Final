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
    SnowSceneObject(glm::vec3 coords, float length, float width, float height, float speed, glm::vec3 direction);
    ~SnowSceneObject();

    virtual void renderShadowScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) = 0;
    virtual void renderPhongScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes) = 0;
    BoundingBox getBoundingBox();
    glm::vec3 getCoords();
    void setDirection(glm::vec3 direction);
    void setPosition(glm::vec3 position);
    glm::vec3 getNewPosition();

    virtual void makeObject(){}
    float getLength();
    float getWidth();
    float getHeight();
    glm::vec3 getDirection();

    static glm::vec3 getRandomDirection();
    static float getRandomSpeed();

protected:

    glm::vec3 m_coords;
    float m_length;
    float m_width;
    float m_height;
    BoundingBox m_boundingBox;
    glm::vec3 m_direction;
    float m_speed;
    const static float maxSpeed;
};


#endif // OPENGLSCENEOBJECT_H
