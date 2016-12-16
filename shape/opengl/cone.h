#ifndef CONE_H
#define CONE_H

#include "openglshape.h"
#include "circle.h"

class Cone : public OpenGLShape {

public:
    Cone(float diameter, float height, int xTess, int yTess, glm::mat4x4 transform);
    ~Cone();  // deconstruct a Cone

    void draw() override; // draw

private:
    float m_height; // height
    int m_xTess; // x tesselation
    int m_yTess; // y tesselation
    glm::mat4x4 m_transform; // transform
    float m_theta; // Cone theta
    float m_diameter; // diameter of Cone
    glm::vec4 getNormal(float angle); // get normal at angle
    void tesselate() override;  // tesselate a Cone
    std::unique_ptr<Circle> m_base; // base of Cone
    void render() override; // render shape
    void renderBase(); // render base
    glm::vec2 getTextureMap(glm::vec4 intersect);

};

#endif // CONE_H
