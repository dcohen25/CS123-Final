#include "implicitcube.h"

#include "rootsolver.h"
#include <iostream>


ImplicitCube::ImplicitCube() :
    m_top(glm::vec4(0.0, .5, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0)),
    m_bottom(glm::vec4(0.0, -.5, 0.0, 0.0), glm::vec4(0.0, -1.0, 0.0, 0.0)),
    m_left(glm::vec4(-.5, 0.0, 0.0, 0.0), glm::vec4(-1.0, 0.0, 0.0, 0.0)),
    m_right(glm::vec4(.5, 0.0, 0.0, 0.0), glm::vec4(1.0, 0.0, 0.0, 0.0)),
    m_front(glm::vec4(0.0, 0.0, -.5, 0.0), glm::vec4(0.0, 0.0, -1.0, 0.0)),
    m_back(glm::vec4(0.0, 0.0, .5, 0.0), glm::vec4(0.0, 0.0, 1.0, 0.0))
{
}

ImplicitCube::~ImplicitCube(){

}

float ImplicitCube::intersect(glm::vec4 p_eye, glm::vec4 d){
   std::vector<float> roots;
   float t1 = m_top.intersect(p_eye, d);
   float t2 = m_bottom.intersect(p_eye, d);
   float t3 = m_left.intersect(p_eye, d);
   float t4 = m_right.intersect(p_eye, d);
   float t5 = m_front.intersect(p_eye, d);
   float t6 = m_back.intersect(p_eye, d);

   if (t1 != -1){
       roots.push_back(t1);
   }
   if (t2 != -1){
       roots.push_back(t2);
   }
   if (t3 != -1){
       roots.push_back(t3);
   }
   if (t4 != -1){
       roots.push_back(t4);
   }
   if (t5 != -1){
       roots.push_back(t5);
   }
   if (t6 != -1){
       roots.push_back(t6);
   }
   return RootSolver::getSmallestRoot(roots);
}

glm::vec2 ImplicitCube::getTextureMap(glm::vec4 intersect){
    glm::vec2 uvCoords;
    if (glm::abs(intersect.y + .5) < .001f){
        uvCoords = glm::vec2(intersect.x + .5, -intersect.z + .5);
    }
    else if (glm::abs(intersect.y - .5) < .001f){
        uvCoords = glm::vec2(intersect.x + .5, intersect.z + .5);
    }
    else if (glm::abs(intersect.x + .5) < .001f){
        uvCoords = glm::vec2(intersect.z + .5, -intersect.y + .5);
    }
    else if (glm::abs(intersect.x - .5) < .001f){
        uvCoords = glm::vec2(-intersect.z + .5, -intersect.y + .5);
    }
    else if (glm::abs(intersect.z - .5) < .001f){
        uvCoords = glm::vec2(intersect.x + .5, -intersect.y + .5);
    }
    else if (glm::abs(intersect.z + .5) < .001f){
        uvCoords = glm::vec2(-intersect.x + .5, -intersect.y + .5);
    }
    return uvCoords;
}

glm::vec4 ImplicitCube::getNormal(glm::vec4 intersect){
    glm::vec4 normal;
    if (glm::abs(intersect.y + .5) < .001f){
        normal = glm::vec4(0, -1, 0, 0);
    }
    else if (glm::abs(intersect.y - .5) < .001f){
        normal = glm::vec4(0, 1, 0, 0);
    }
    else if (glm::abs(intersect.x + .5) < .001f){
        normal = glm::vec4(-1, 0, 0, 0);
    }
    else if (glm::abs(intersect.x - .5) < .001f){
        normal = glm::vec4(1, 0, 0, 0);
    }
    else if (glm::abs(intersect.z - .5) < .001f){
        normal = glm::vec4(0, 0, 1, 0);
    }
    else if (glm::abs(intersect.z + .5) < .001f){
        normal = glm::vec4(0, 0, -1, 0);
    }
    return normal;
}
