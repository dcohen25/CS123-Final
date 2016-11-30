#include "implicitcylinder.h"

#include "glm.hpp"
#include "implicitcircle.h"
#include "rootsolver.h"

ImplicitCylinder::ImplicitCylinder() :
    m_top(glm::vec4(0, .5, 0, 0), glm::vec4(0, 1, 0, 0)),
    m_bottom(glm::vec4(0, -.5, 0, 0), glm::vec4(0, -1, 0, 0))
{
}

ImplicitCylinder::~ImplicitCylinder(){

}

float ImplicitCylinder::intersect(glm::vec4 p_eye, glm::vec4 d){
   std::vector<float> roots;
   std::vector<float> bodyRoots = intersectBody(p_eye, d);
   float topRoot = intersectTop(p_eye, d);
   float bottomRoot = intersectBottom(p_eye, d);

   roots = bodyRoots;
   if (topRoot != -1){
       roots.push_back(topRoot);
   }
   if (bottomRoot != -1){
       roots.push_back(bottomRoot);
   }

   return RootSolver::getSmallestRoot(roots);
}

glm::vec2 ImplicitCylinder::getTextureMap(glm::vec4 intersect){
    if (glm::abs(intersect.y + .5) < .001f || glm::abs(intersect.y - .5) < .001f){
        return m_top.getTextureMap(intersect);
    }
    glm::vec2 coords;
    coords.y = -intersect.y + .5;
    float angle = atan2(intersect.z, intersect.x);
    if (angle < 0){
        coords.x = -angle / (2.0 * M_PI);
    }
    else {
        coords.x = 1 - (angle / (2.0 * M_PI));
    }
    return coords;
}

float ImplicitCylinder::intersectTop(glm::vec4 p_eye, glm::vec4 d){
    return m_top.intersect(p_eye, d);
}

float ImplicitCylinder::intersectBottom(glm::vec4 p_eye, glm::vec4 d){
    return m_bottom.intersect(p_eye, d);
}

std::vector<float> ImplicitCylinder::intersectBody(glm::vec4 p_eye, glm::vec4 d){
    float A = pow(d.x, 2.0) + pow(d.z, 2.0);
    float B = (2.0 * p_eye.x * d.x) + (2.0 * p_eye.z * d.z);
    float C = pow(p_eye.x, 2.0) + pow(p_eye.z, 2.0) - .25;

    std::vector<float> roots = RootSolver::getQuadraticRoots(A, B, C);
    std::vector<float> validRoots = filterValidRoots(p_eye, d, roots);

    return validRoots;
}

glm::vec4 ImplicitCylinder::getNormal(glm::vec4 intersect){
    if (glm::abs(intersect.y + .5) < 0.001f){
        return glm::vec4(0.0, -1.0, 0.0, 0.0);
    }
    if (glm::abs(intersect.y - .5) < 0.001f){
        return glm::vec4(0.0, 1.0, 0.0, 0.0);
    }
    float angle = atan2(intersect.z, intersect.x);
    glm::vec4 normal(cos(angle), 0.0, sin(angle), 0.0);
    return glm::normalize(normal);
}

std::vector<float> ImplicitCylinder::filterValidRoots(glm::vec4 p_eye, glm::vec4 d, std::vector<float> roots){
    std::vector<float> validRoots;
    for (int i = 0; i < roots.size(); i++){
         float root = roots[i];
         glm::vec4 coord = p_eye + (root * d);
         if (coord.y <= .5 && coord.y >= -.5 && root >= 0){
             validRoots.push_back(root);
         }
    }
    return validRoots;
}
