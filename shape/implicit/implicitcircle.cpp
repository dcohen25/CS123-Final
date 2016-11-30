#include "implicitcircle.h"
#include "rootsolver.h"

ImplicitCircle::ImplicitCircle(glm::vec4 center, glm::vec4 normal) :
    m_center(center),
    m_normal(normal)
{

}

ImplicitCircle::~ImplicitCircle() {

}

float ImplicitCircle::intersect(glm::vec4 p_eye, glm::vec4 d){
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

glm::vec2 ImplicitCircle::getTextureMap(glm::vec4 intersect){
    return glm::vec2(intersect.x + .5, -intersect.z + .5);
}

bool ImplicitCircle::isValidIntersection(glm::vec4 intersection){
    return pow(intersection.x, 2.0) + pow(intersection.z, 2.0) <= pow(.5, 2.0);
}

glm::vec4 ImplicitCircle::getNormal(glm::vec4 intersect){
    return m_normal;
}



