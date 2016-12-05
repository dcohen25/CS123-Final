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
#include "utils.h"
#include "tree.h"

using namespace CS123::GL;

SnowSceneTile::SnowSceneTile(glm::vec3 coords, float size, int numTrees, int numSnowmen, float treeRadius, float snowmanRadius, float maxSnowmanHeight, float maxTreeHeight) :
    OpenGLSceneTile(coords, size),
    m_numTrees(numTrees),
    m_numSnowmen(numSnowmen),
    m_treeRadius(treeRadius),
    m_snowmanRadius(snowmanRadius),
    m_maxSnowmanHeight(maxSnowmanHeight),
    m_maxTreeHeight(maxTreeHeight)
{
    initScene();
}

SnowSceneTile::SnowSceneTile(){

}

SnowSceneTile::~SnowSceneTile()
{
}

// Initialize Scene
void SnowSceneTile::initScene(){
    initTrees();
    //initSnowmen();
   // initSnow();
}

void SnowSceneTile::initTrees(){
    for (int i = 0; i < m_numTrees; i++){
        Tree tree = Tree(m_maxTreeHeight, m_treeRadius);
        setRandomPositionOnTile(tree);
        m_sceneObjects.push_back(tree);
    }
}

void SnowSceneTile::setRandomPositionOnTile(OpenGLSceneObject &object){
    glm::mat4x4 transform;
    transform = glm::translate(transform, Utils::getRandomPositionOnTile(m_tileSize, m_coords));
    object.transform(transform);
}

//void SnowSceneTile::initSnowmen(){
//    for (int i = 0; i < m_numSnowmen; i++){
//        Snowman snowman = Snowman();
//        m_sceneObjects.push_back(snowman);
//    }
//}

//std::vector<CS123ScenePrimitive> SnowSceneTile::makeSnowman(){
//    std::vector<CS123ScenePrimitive> snowman;
//    CS123ScenePrimitive top = makeSnowmanSphere();
//    CS123ScenePrimitive middle = makeSnowmanSphere();
//    CS123ScenePrimitive bottom = makeSnowmanSphere();
//    snowman.push_back(top);
//    snowman.push_back(middle);
//    snowman.push_back(bottom);
//    return snowman;
//}

//CS123ScenePrimitive SnowSceneTile::makeSnowmanSphere(){
//    CS123ScenePrimitive snowmanSphere;
//    snowmanSphere.type = PrimitiveType::PRIMITIVE_SPHERE;
//    snowmanSphere.material.clear();
//    snowmanSphere.material.cAmbient.r = .5f;
//    snowmanSphere.material.cAmbient.g = .5f;
//    snowmanSphere.material.cAmbient.b = .5f;
//    snowmanSphere.material.cDiffuse.r = 1.f;
//    snowmanSphere.material.cDiffuse.g = 1.f;
//    snowmanSphere.material.cDiffuse.b = 1.f;
//    snowmanSphere.material.cSpecular.r = snowmanSphere.material.cSpecular.g = snowmanSphere.material.cSpecular.b = 1;
//    snowmanSphere.material.shininess = 64;

//    return snowmanSphere;
//}

//void SnowSceneTile::initSnowPrimitive(){
//    CS123ScenePrimitive snow = makeSnow();
//    m_primitives.push_back(snow);
//}

//CS123ScenePrimitive SnowSceneTile::makeSnow(){
//    CS123ScenePrimitive snow;
//    snow.type = PrimitiveType::PRIMITIVE_CUBE;
//    snow.material.clear();
//    snow.material.cAmbient.r = 1.f;
//    snow.material.cAmbient.g = 1.f;
//    snow.material.cAmbient.b = 1.f;
//    snow.material.cDiffuse.r = .6f;
//    snow.material.cDiffuse.g = .6f;
//    snow.material.cDiffuse.b = .6f;
//    snow.material.cSpecular.r = snow.material.cSpecular.g = snow.material.cSpecular.b = 1;
//    snow.material.shininess = 64;

//    return snow;
//}

//void SnowSceneTile::initSnowTransformation(){
//   glm::mat4x4 transformation = computeSnowTransformation();
//   m_transformations.push_back(transformation);
//}


//void SnowSceneTile::initSnowmanTransformations(){
//    for (int i = 0; i < SnowSceneTile::m_numSnowmen; i++){
//        std::vector<glm::mat4x4> transformation = computeSnowmanTransformation();
//        for (int j = 0; j < transformation.size(); j++){
//            m_transformations.push_back(transformation[j]);
//        }
//    }
//}

//std::vector<glm::mat4x4> SnowSceneTile::computeSnowmanTransformation(){
//    std::vector<glm::mat4x4> transformation;
//    glm::mat4x4 pos = glm::translate(glm::mat4x4(), getRandomObjectPosition());
//    glm::mat4x4 top = pos * computeSnowmanTopTransformation();
//    glm::mat4x4 middle = pos * computeSnowmanMiddleTransformation();
//    glm::mat4x4 bottom = pos * computeSnowmanBottomTransformation();
//    transformation.push_back(top);
//    transformation.push_back(middle);
//    transformation.push_back(bottom);
//    return transformation;
//}

//glm::mat4x4 SnowSceneTile::computeSnowmanBottomTransformation(){
//    glm::mat4x4 transformation;
//    transformation = glm::translate(transformation, glm::vec3(0, SnowSceneTile::m_snowmanRadius, 0));
//    transformation = glm::scale(transformation, glm::vec3(SnowSceneTile::m_snowmanRadius * 2, SnowSceneTile::m_snowmanRadius * 2, SnowSceneTile::m_snowmanRadius * 2));
//    return transformation;
//}

//glm::mat4x4 SnowSceneTile::computeSnowmanMiddleTransformation(){
//    glm::mat4x4 transformation;
//    float radius = SnowSceneTile::m_snowmanRadius * (2.f / 3.f);
//    transformation = glm::translate(transformation, glm::vec3(0, radius + (SnowSceneTile::m_snowmanRadius * 2), 0));
//    transformation = glm::scale(transformation, glm::vec3(radius * 2, radius * 2, radius * 2));
//    return transformation;
//}

//glm::mat4x4 SnowSceneTile::computeSnowmanTopTransformation(){
//    glm::mat4x4 transformation;
//    float radius = SnowSceneTile::m_snowmanRadius * (1.f / 2.f);
//    transformation = glm::translate(transformation, glm::vec3(0, radius + (SnowSceneTile::m_snowmanRadius * 2) + (SnowSceneTile::m_snowmanRadius * (2.f / 3.f) * 2), 0));
//    transformation = glm::scale(transformation, glm::vec3(radius * 2, radius * 2, radius * 2));
//    return transformation;
//}

//glm::mat4x4 SnowSceneTile::computeSnowTransformation(){
//    glm::mat4x4 snowTransformation;
//    snowTransformation = glm::translate(snowTransformation, glm::vec3(m_coords.x, 0, m_coords.y));
//    snowTransformation = glm::scale(snowTransformation, glm::vec3(SnowSceneTile::m_gridSize, 0.f, SnowSceneTile::m_gridSize));
//    return snowTransformation;
//}
