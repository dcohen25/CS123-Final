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
    snow.type = PrimitiveType::PRIMITIVE_CUBE;
    snow.material.clear();
    snow.material.cAmbient.r = 1.f;
    snow.material.cAmbient.g = 1.f;
    snow.material.cAmbient.b = 1.f;
    snow.material.cDiffuse.r = .6f;
    snow.material.cDiffuse.g = .6f;
    snow.material.cDiffuse.b = .6f;
    snow.material.cSpecular.r = snow.material.cSpecular.g = snow.material.cSpecular.b = 1;
    snow.material.shininess = 100;

    m_primitives.push_back(snow);
}

void Snow::initSnowTransformation(){
    glm::mat4x4 snowTransformation;
    snowTransformation = glm::translate(snowTransformation, m_coords);
    snowTransformation = glm::scale(snowTransformation, glm::vec3(m_width, m_height, m_length));

    m_transformations.push_back(snowTransformation);
}
