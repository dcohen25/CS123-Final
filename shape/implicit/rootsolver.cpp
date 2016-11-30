#include "rootsolver.h"

#include <iostream>
RootSolver::RootSolver()
{

}
RootSolver::~RootSolver(){

}

std::vector<float> RootSolver::getQuadraticRoots(float A, float B, float C){
    std::vector<float> roots;
    float discriminant = getDiscriminant(A, B, C);
    int numRoots = getNumberOfRoots(discriminant);
    if (numRoots == 1){
        float t1 = getQuadraticRootOne(A, B, C);
        roots.push_back(t1);
    }
    if (numRoots == 2){
        float t1 = getQuadraticRootOne(A, B, C);
        float t2 = getQuadraticRootTwo(A, B, C);
        roots.push_back(t1);
        roots.push_back(t2);
    }
    return roots;
}

float RootSolver::getPlanarRoot(glm::vec4 p_eye, glm::vec4 d, glm::vec4 center, glm::vec4 normal){
    float v1 = (normal.x * center.x) + (normal.y * center.y) + (normal.z * center.z);
    float v2 = (normal.x * p_eye.x) + (normal.y * p_eye.y) + (normal.z * p_eye.z);
    float v3 = (normal.x * d.x) + (normal.y * d.y) + (normal.z * d.z);
    float t = (v1 - v2) / v3;
    return t;
}

float RootSolver::getSmallestRoot(std::vector<float> roots){
    if (roots.size() == 0){
        return -1;
    }
    float min_t = std::numeric_limits<float>::max();
    for (int i = 0; i < roots.size(); i++){
        if (roots[i] < min_t){
            min_t = roots[i];
        }
    }
    return min_t;
}


float RootSolver::getQuadraticRootOne(float A, float B, float C){
    float discriminant = getDiscriminant(A, B, C);
    float t = (-B + sqrt(discriminant)) / (2.0 * A);
    return t;
}

float RootSolver::getQuadraticRootTwo(float A, float B, float C){
    float discriminant = getDiscriminant(A, B, C);
    float t = (-B - sqrt(discriminant)) / (2.0 * A);
    return t;
}

float RootSolver::getDiscriminant(float A, float B, float C){
    return pow(B, 2.0) - (4.0 * A * C);
}

int RootSolver::getNumberOfRoots(float discriminant){
    if (discriminant < 0){
        return 0;
    }
    if (discriminant == 0){
        return 1;
    }
    if (discriminant > 0){
        return 2;
    }
}

bool RootSolver::isValidRoot(float root){
    return root >= 0;
}
