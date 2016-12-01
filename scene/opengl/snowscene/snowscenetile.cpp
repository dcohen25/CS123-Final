#include "snowscenetile.h"

#include "GL/glew.h"
#include <QGLWidget>
#include "ui/view.h"
#include "lib/resourceloader.h"
#include "glm.hpp"
#include "lib/cs123scenedata.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include <iostream>
#include "glm/gtx/string_cast.hpp"

using namespace CS123::GL;

SnowSceneTile::SnowSceneTile(float x, float y, int numTrees, int numSnowmen, float treeRadius, float snowmanRadius, float gridSize) :
    m_numTrees(numTrees),
    m_numSnowmen(numSnowmen),
    m_treeRadius(treeRadius),
    m_snowmanRadius(snowmanRadius),
    m_gridSize(gridSize),
    m_coords(x, y)
{
    initScene();
}

SnowSceneTile::SnowSceneTile(){

}

SnowSceneTile::~SnowSceneTile()
{
}

std::vector<CS123ScenePrimitive> SnowSceneTile::getPrimitives(){
    return m_primitives;
}

std::vector<glm::mat4x4> SnowSceneTile::getTransformations(){
    return m_transformations;
}

// Initialize Scene
void SnowSceneTile::initScene(){
    initPrimitives();
    initTransformations();
    initGlobals();
}

void SnowSceneTile::initPrimitives(){
    initTreePrimitives();
    initSnowmanPrimitives();
    initSnowPrimitive();
}

void SnowSceneTile::initTransformations(){
    initTreeTransformations();
    initSnowmanTransformations();
    initSnowTransformation();
}

void SnowSceneTile::initTreePrimitives(){
    for (int i = 0; i < m_numTrees; i++){
        CS123ScenePrimitive tree = makeTree();
        m_primitives.push_back(tree);
    }
}



CS123ScenePrimitive SnowSceneTile::makeSnow(){
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
    snow.material.shininess = 64;

    return snow;
}

CS123ScenePrimitive SnowSceneTile::makeTree(){
    CS123ScenePrimitive tree;
    tree.type = PrimitiveType::PRIMITIVE_CONE;
    tree.material.clear();
    tree.material.cAmbient.g = .3f;
    tree.material.cDiffuse.g = 1.f;
    tree.material.cSpecular.r = tree.material.cSpecular.g = tree.material.cSpecular.b = 1;
    tree.material.shininess = 64;

    return tree;
}

void SnowSceneTile::initTreeTransformations(){
    for (int i = 0; i < m_numTrees; i++){
        glm::mat4x4 transformation = computeTreeTransformation();
        m_transformations.push_back(transformation);
    }
}

void SnowSceneTile::initSnowTransformation(){
   glm::mat4x4 transformation = computeSnowTransformation();
   m_transformations.push_back(transformation);
}


void SnowSceneTile::initSnowmanTransformations(){
    for (int i = 0; i < m_numSnowmen; i++){
        std::vector<glm::mat4x4> transformation = computeSnowmanTransformation();
        for (int j = 0; j < transformation.size(); j++){
            m_transformations.push_back(transformation[j]);
        }
    }
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


glm::vec3 SnowSceneTile::getRandomObjectPosition(){
    glm::vec3 pos;
    pos.x = (((float) rand() / RAND_MAX) * m_gridSize) - (m_gridSize / 2.f) + m_coords.x;
    pos.y = 0.f;
    pos.z = (((float) rand() / RAND_MAX) * m_gridSize)  - (m_gridSize / 2.f) + m_coords.y;
    return pos;
}

glm::mat4x4 SnowSceneTile::computeTreeTransformation(){
    glm::mat4x4 treeTransformation;
    glm::vec3 treePosition = getRandomObjectPosition();
    treePosition.y += .5f;
    treeTransformation = glm::translate(treeTransformation, treePosition);
    return treeTransformation;
}

glm::mat4x4 SnowSceneTile::computeSnowTransformation(){
    glm::mat4x4 snowTransformation;
    snowTransformation = glm::translate(snowTransformation, glm::vec3(m_coords.x, 0, m_coords.y));
    snowTransformation = glm::scale(snowTransformation, glm::vec3(SnowSceneTile::m_gridSize, 0.f, SnowSceneTile::m_gridSize));
    return snowTransformation;
}

void SnowSceneTile::initGlobals(){

}
