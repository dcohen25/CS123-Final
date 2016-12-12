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
#include "scene/utils.h"
#include "tree.h"
#include "snowman.h"
#include "snow.h"

using namespace CS123::GL;

const float SnowSceneTile::tileSize = 50.f;
const int SnowSceneTile::numTrees = 40;
const int SnowSceneTile::numSnowmen = 4;

SnowSceneTile::SnowSceneTile(glm::vec3 coords) :
    m_coords(coords),
    m_boundingBox(coords, SnowSceneTile::tileSize, SnowSceneTile::tileSize, SnowSceneTile::tileSize)
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
    initSnowmen();
    initSnow();
}

void SnowSceneTile::initSnow(){
    Snow snow = Snow(m_coords);
    m_sceneObjects.push_back(snow);
}

void SnowSceneTile::initTrees(){
    for (int i = 0; i < SnowSceneTile::numTrees; i++){
        float heightFactor = glm::clamp(Utils::getRandomValue(), .5f, 1.f);
        float diameterFactor = glm::clamp(Utils::getRandomValue(), .5f, 1.f);
        float diameter = diameterFactor * Tree::maxDiameter;
        float height = heightFactor * Tree::maxHeight;
        glm::vec3 coords = getRandomPositionOnTile();
        coords.y += height / 2.f;
        Tree tree = Tree(coords, diameter, height);
        m_sceneObjects.push_back(tree);
    }
}

void SnowSceneTile::initSnowmen(){
    for (int i = 0; i < SnowSceneTile::numSnowmen; i++){
        float diameterFactor = glm::clamp(Utils::getRandomValue(), .5f, 1.f);
        float diameter = diameterFactor * Snowman::maxDiameter;
        glm::vec3 coords = getRandomPositionOnTile();
        float height = Snowman::computeSnowmanHeight(diameter);
        coords += height / 2.f;
        Snowman snowman = Snowman(coords, diameter);
        m_sceneObjects.push_back(snowman);
    }
}

void SnowSceneTile::render(View *context, std::unique_ptr<CS123Shader> &shader, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    for (int i = 0; i < m_sceneObjects.size(); i++){
        if (context->getCamera()->isVisible(m_sceneObjects[i].getBoundingBox())){
            m_sceneObjects[i].render(shader, shapes);
        }
    }
}

glm::vec3 SnowSceneTile::getRandomPositionOnTile(){
    glm::vec3 pos;
    pos.x = (Utils::getRandomValue() * SnowSceneTile::tileSize) - (SnowSceneTile::tileSize / 2.f) + m_coords.x;
    pos.y = 0.f;
    pos.z = (Utils::getRandomValue() * SnowSceneTile::tileSize)  - (SnowSceneTile::tileSize / 2.f) + m_coords.z;
    return pos;
}

BoundingBox SnowSceneTile::getBoundingBox(){
    return m_boundingBox;
}
