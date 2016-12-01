#include "snowman.h"

Snowman::Snowman()
{
}


void SnowSceneTile::initSnowmanPrimitives(){
    for (int i = 0; i < m_numSnowmen; i++){
        std::vector<CS123ScenePrimitive> snowman = makeSnowman();
        for (int j = 0; j < snowman.size(); j++){
            m_primitives.push_back(snowman[j]);
        }
    }
}

std::vector<CS123ScenePrimitive> SnowSceneTile::makeSnowman(){
    std::vector<CS123ScenePrimitive> snowman;
    std::vector<CS123ScenePrimitive> hat = makeSnowmanHat();
    std::vector<CS123ScenePrimitive> body = makeSnowmanBody();
    for (int i = 0; i < hat.size(); i++){
        snowman.push_back(hat[i]);
    }
    for (int i = 0; i < body.size(); i++){
        snowman.push_back(body[i]);
    }
    return snowman;
}

std::vector<CS123ScenePrimitive> SnowSceneTile::makeSnowmanBody(){
    std::vector<CS123ScenePrimitive> snowmanBody;
    CS123ScenePrimitive top = makeSnowmanTop();
    CS123ScenePrimitive middle = makeSnowmanMiddle();
    CS123ScenePrimitive base = makeSnowmanBottom();

}

std::vector<CS123ScenePrimitive> SnowSceneTile::makeSnowmanFace(){
    makeSnowmanSphere()
}

CS123ScenePrimitive SnowSceneTile::makeSnowmanSphere(){
    CS123ScenePrimitive snowmanSphere;
    snowmanSphere.type = PrimitiveType::PRIMITIVE_SPHERE;
    snowmanSphere.material.clear();
    snowmanSphere.material.cAmbient.r = .5f;
    snowmanSphere.material.cAmbient.g = .5f;
    snowmanSphere.material.cAmbient.b = .5f;
    snowmanSphere.material.cDiffuse.r = 1.f;
    snowmanSphere.material.cDiffuse.g = 1.f;
    snowmanSphere.material.cDiffuse.b = 1.f;
    snowmanSphere.material.cSpecular.r = snowmanSphere.material.cSpecular.g = snowmanSphere.material.cSpecular.b = 1;
    snowmanSphere.material.shininess = 64;

    return snowmanSphere;
}

void SnowSceneTile::initSnowPrimitive(){
    CS123ScenePrimitive snow = makeSnow();
    m_primitives.push_back(snow);
}

glm::mat4x4 SnowSceneTile::computeSnowmanBottomTransformation(){
    glm::mat4x4 transformation;
    transformation = glm::translate(transformation, glm::vec3(0, SnowSceneTile::m_snowmanRadius, 0));
    transformation = glm::scale(transformation, glm::vec3(SnowSceneTile::m_snowmanRadius * 2, SnowSceneTile::m_snowmanRadius * 2, SnowSceneTile::m_snowmanRadius * 2));
    return transformation;
}

glm::mat4x4 SnowSceneTile::computeSnowmanMiddleTransformation(){
    glm::mat4x4 transformation;
    float radius = SnowSceneTile::m_snowmanRadius * (2.f / 3.f);
    transformation = glm::translate(transformation, glm::vec3(0, radius + (SnowSceneTile::m_snowmanRadius * 2), 0));
    transformation = glm::scale(transformation, glm::vec3(radius * 2, radius * 2, radius * 2));
    return transformation;
}

glm::mat4x4 SnowSceneTile::computeSnowmanTopTransformation(){
    glm::mat4x4 transformation;
    float radius = SnowSceneTile::m_snowmanRadius * (1.f / 2.f);
    transformation = glm::translate(transformation, glm::vec3(0, radius + (SnowSceneTile::m_snowmanRadius * 2) + (SnowSceneTile::m_snowmanRadius * (2.f / 3.f) * 2), 0));
    transformation = glm::scale(transformation, glm::vec3(radius * 2, radius * 2, radius * 2));
    return transformation;
}

std::vector<glm::mat4x4> SnowSceneTile::computeSnowmanTransformation(){
    std::vector<glm::mat4x4> transformation;
    glm::mat4x4 pos = glm::translate(glm::mat4x4(), getRandomObjectPosition());
    glm::mat4x4 top = pos * computeSnowmanTopTransformation();
    glm::mat4x4 middle = pos * computeSnowmanMiddleTransformation();
    glm::mat4x4 bottom = pos * computeSnowmanBottomTransformation();
    transformation.push_back(top);
    transformation.push_back(middle);
    transformation.push_back(bottom);
    return transformation;
}


void SnowSceneTile::initSnowmanTransformations(){
    for (int i = 0; i < m_numSnowmen; i++){
        std::vector<glm::mat4x4> transformation = computeSnowmanTransformation();
        for (int j = 0; j < transformation.size(); j++){
            m_transformations.push_back(transformation[j]);
        }
    }
}
