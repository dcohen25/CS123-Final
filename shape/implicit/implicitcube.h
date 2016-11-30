#ifndef IMPLICITCUBE_H
#define IMPLICITCUBE_H


#include "glm.hpp"
#include "implicitsquare.h"
#include "implicitshape.h"


class ImplicitCube : public ImplicitShape
{
public:
    ImplicitCube();
    ~ImplicitCube();

    glm::vec4 getNormal(glm::vec4 intersect) override;
    float intersect(glm::vec4 p_eye, glm::vec4 d) override;
    glm::vec2 getTextureMap(glm::vec4 intersect) override;

private:
    ImplicitSquare m_top;
    ImplicitSquare m_bottom;
    ImplicitSquare m_left;
    ImplicitSquare m_right;
    ImplicitSquare m_front;
    ImplicitSquare m_back;

};

#endif // IMPLICITCUBE_H
