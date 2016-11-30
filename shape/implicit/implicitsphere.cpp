#include "implicitsphere.h"

#include "rootsolver.h"
ImplicitSphere::ImplicitSphere()
{
}

ImplicitSphere::~ImplicitSphere()
{
}


float ImplicitSphere::intersect(glm::vec4 p_eye, glm::vec4 d){
    float A = pow(d.x, 2.0) + pow(d.z, 2.0) + pow(d.y, 2.0);
    float B = (2.0 * p_eye.x * d.x) + (2.0 * p_eye.z * d.z) + (2.0 * p_eye.y * d.y);
    float C = pow(p_eye.x, 2.0) + pow(p_eye.z, 2.0) + pow(p_eye.y, 2.0) - .25;

    std::vector<float> roots = RootSolver::getQuadraticRoots(A, B, C);
    std::vector<float> validRoots = filterValidRoots(p_eye, d, roots);

    return RootSolver::getSmallestRoot(validRoots);
}

glm::vec2 ImplicitSphere::getTextureMap(glm::vec4 intersect){
    glm::vec2 coords;
    float phi = asin(intersect.y / .5);
    coords.y = -(phi / M_PI) + .5;
    if (coords.y == 0 || coords.y == 1){
        coords.x = .5;
    }
    else {
        float theta = atan2(intersect.z, intersect.x);
        if (theta < 0){
            coords.x = -theta / (2.0 * M_PI);
        }
        else {
            coords.x = 1 - (theta / (2.0 * M_PI));
        }
    }
    return coords;
}

glm::vec4 ImplicitSphere::getNormal(glm::vec4 intersect){
    glm::vec4 normal(intersect.x, intersect.y, intersect.z, 0.0);
    return glm::normalize(normal);
}

std::vector<float> ImplicitSphere::filterValidRoots(glm::vec4 p_eye, glm::vec4 d, std::vector<float> roots){
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

