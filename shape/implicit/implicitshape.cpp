#include "implicitshape.h"
#include <vector>

ImplicitShape::ImplicitShape()
{

}
ImplicitShape::~ImplicitShape(){

}

// intersect ray
float ImplicitShape::intersect(glm::vec4 p_eye, glm::vec4 d){}

// get normal at point of intersection
glm::vec4 ImplicitShape::getNormal(glm::vec4 intersect){}

// texture map at point of intersection
glm::vec2 ImplicitShape::getTextureMap(glm::vec4 intersect){}
