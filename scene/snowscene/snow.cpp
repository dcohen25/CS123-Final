#include "snow.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "snowscenetile.h"

Snow::Snow(glm::vec3 coords) :
    SnowSceneObject(coords, SnowSceneTile::tileSize, SnowSceneTile::tileSize, 0)
{
    initSnow();
}

Snow::~Snow(){

}

void Snow::initSnow(){
    initSnowPrimitive();
    initSnowTransformation();
}

void Snow::initSnowPrimitive(){
    CS123ScenePrimitive snow;
    snow.type = PrimitiveType::PRIMITIVE_TERRAIN;
    snow.material.clear();
    snow.material.cAmbient.r = .3f;
    snow.material.cAmbient.g = .3f;
    snow.material.cAmbient.b = .3f;
    snow.material.cDiffuse.r = .3f;
    snow.material.cDiffuse.g = .3f;
    snow.material.cDiffuse.b = .3f;
    snow.material.cSpecular.r = snow.material.cSpecular.g = snow.material.cSpecular.b = 0;
    snow.material.shininess = 0;

    m_primitives.push_back(snow);
}

void Snow::initSnowTransformation(){
    glm::mat4x4 snowTransformation;
    snowTransformation = glm::translate(snowTransformation, glm::vec3(m_coords.x, m_coords.y, m_coords.z));

    m_transformations.push_back(snowTransformation);
}
