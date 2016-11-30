#include "implicitcone.h"

#include <vector>
#include <math.h>
#include <memory>
#include "rootsolver.h"
#include <iostream>

ImplicitCone::ImplicitCone() :
    m_base(glm::vec4(0, -.5, 0, 0), glm::vec4(0, -1, 0, 1))
{

}

ImplicitCone::~ImplicitCone(){

}


float ImplicitCone::intersect(glm::vec4 p_eye, glm::vec4 d){
   std::vector<float> roots;
   std::vector<float> bodyRoots = intersectBody(p_eye, d);
   float baseRoot = intersectBase(p_eye, d);
   roots = bodyRoots;
   if (baseRoot != -1){
       roots.push_back(baseRoot);
   }

   return RootSolver::getSmallestRoot(roots);
}

float ImplicitCone::intersectBase(glm::vec4 p_eye, glm::vec4 d){
    return m_base.intersect(p_eye, d);
}

glm::vec2 ImplicitCone::getTextureMap(glm::vec4 intersect){
    if (glm::abs(intersect.y + .5) < .001f){
        return m_base.getTextureMap(intersect);
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

std::vector<float> ImplicitCone::intersectBody(glm::vec4 p_eye, glm::vec4 d){
    float A = pow(d.x, 2.0) + pow(d.z, 2.0) - (.25 * pow(d.y, 2.0));
    float B = (2.0 * p_eye.x * d.x) + (2.0 * p_eye.z * d.z) - (.5 * p_eye.y * d.y) + (.25 * d.y);
    float C = pow(p_eye.x, 2.0) + pow(p_eye.z, 2.0) - (.25 * pow(p_eye.y, 2.0)) + (.25 * p_eye.y) - .0625;

    std::vector<float> roots = RootSolver::getQuadraticRoots(A, B, C);
    std::vector<float> validRoots = filterValidRoots(p_eye, d, roots);

    return validRoots;
}

glm::vec4 ImplicitCone::getNormal(glm::vec4 intersect){
    if (glm::abs(intersect.y + .5) < .001f){
        return glm::vec4(0.0, -1.0, 0.0, 1.0);
    }
    float angle = atan2(intersect.z, intersect.x);
    // get slope of cone
    float x1 = .5;
    float y1 = -.5;
    float x2 = 0;
    float y2 = .5;
    float slope = (y2 - y1) / (x2 - x1);
    // get normal x and y magnitudes
    float y = 1.0 / sqrt((slope * slope) + 1);
    // get normal vector
    glm::vec4 normal(cos(angle), y, sin(angle), 0.0);
    return glm::normalize(normal);
}

std::vector<float> ImplicitCone::filterValidRoots(glm::vec4 p_eye, glm::vec4 d, std::vector<float> roots){
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
