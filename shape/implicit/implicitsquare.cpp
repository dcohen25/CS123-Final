#include "implicitsquare.h"

#include "rootsolver.h"
#include <iostream>
#include "string"
#include <glm/gtx/string_cast.hpp>


ImplicitSquare::ImplicitSquare(glm::vec4 center, glm::vec4 normal) :
    m_center(center),
    m_normal(normal)
{
}

ImplicitSquare::~ImplicitSquare() {

}

float ImplicitSquare::intersect(glm::vec4 p_eye, glm::vec4 d){
    float root = RootSolver::getPlanarRoot(p_eye, d, m_center, m_normal);
    if (!RootSolver::isValidRoot(root)){
        return -1;
    }
    glm::vec4 intersection = p_eye + (root * d);
    if (!isValidIntersection(intersection)){
        return -1;
    }
    return root;
}

bool ImplicitSquare::isValidIntersection(glm::vec4 intersection){
    return intersection.x >= -.5 &&
            intersection.x <= .5 &&
            intersection.z >= -.5 &&
            intersection.z <= .5 &&
            intersection.y >= -.5 &&
            intersection.y <= .5;
}

glm::vec4 ImplicitSquare::getNormal(glm::vec4 intersect){
    return m_normal;
}
