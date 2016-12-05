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

class OpenGLSceneObject
{
public:
    OpenGLSceneObject();
    ~OpenGLSceneObject();

    virtual void render(std::unique_ptr<CS123Shader>  &shader);
    void transform(glm::mat4x4 transformation);

protected:
    std::vector<CS123ScenePrimitive> m_primitives;
    std::vector<glm::mat4x4> m_transformations;
    static std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> m_shapes;

private:
    static std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> initMap() {
        std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> m_shapes;
        m_shapes[PrimitiveType::PRIMITIVE_CUBE] = std::make_unique<Cube>(1, 40, glm::mat4x4());
        m_shapes[PrimitiveType::PRIMITIVE_CONE] = std::make_unique<Cone>(1, 1, 40, 40, glm::mat4x4());
        m_shapes[PrimitiveType::PRIMITIVE_SPHERE] = std::make_unique<Sphere>(.5f, 40, 40, glm::mat4x4());
        m_shapes[PrimitiveType::PRIMITIVE_CYLINDER] = std::make_unique<Cylinder>(1, 1, 40, 40, glm::mat4x4());
        return m_shapes;
    }
};


#endif // OPENGLSCENEOBJECT_H
