#include "snowscenetile.h"

#include "scene/utils.h"
#include "tree.h"
#include "snowman.h"
#include "snow.h"
#include "ornament.h"

using namespace CS123::GL;

const float SnowSceneTile::tileSize = 15.f;
const int SnowSceneTile::numTrees = 5;
const int SnowSceneTile::numSnowmen = 3;
const int SnowSceneTile::numOrnaments = 4;

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

void SnowSceneTile::updateSceneObjects(){
    for (int i = 1; i < m_sceneObjects.size(); i++){
        glm::vec3 newPosition = m_sceneObjects[i]->getNewPosition();
        BoundingBox box(newPosition, m_sceneObjects[i]->getLength(), m_sceneObjects[i]->getWidth(), m_sceneObjects[i]->getHeight());
        bool isCollision = false;
        for (int j = 1; j < m_sceneObjects.size(); j++){
            if (i != j){
                if (box.isIntersection(m_sceneObjects[j]->getBoundingBox())){
                    isCollision = true;
                    break;
                }
            }
        }
        if (box.getMaxX() > m_coords.x + SnowSceneTile::tileSize / 2.f ||
                box.getMinX() < m_coords.x - SnowSceneTile::tileSize / 2.f ||
                box.getMinZ() < m_coords.z - SnowSceneTile::tileSize / 2.f ||
                box.getMaxZ() > m_coords.z + SnowSceneTile::tileSize / 2.f){
            isCollision = true;
        }
        if (isCollision){
            m_sceneObjects[i]->setDirection(-m_sceneObjects[i]->getDirection());
        }
        else {
            m_sceneObjects[i]->setPosition(newPosition);
        }
    }
}

// Initialize Scene
void SnowSceneTile::initScene(){
    initSnow();
    initTrees();
    initSnowmen();
    initOrnaments();
}

void SnowSceneTile::initSnow(){
    m_sceneObjects.push_back(std::make_shared<Snow>(m_coords));
}

void SnowSceneTile::initTrees(){
    for (int i = 0; i < SnowSceneTile::numTrees; i++){
        float heightFactor = glm::clamp(Utils::getRandomValue(), .5f, 1.f);
        float diameterFactor = glm::clamp(Utils::getRandomValue(), .5f, 1.f);
        float diameter = diameterFactor * Tree::maxDiameter;
        float height = heightFactor * Tree::maxHeight;
        glm::vec3 coords = getRandomPositionOnTile();
        coords.y += height / 2.f;
        m_sceneObjects.push_back(std::make_shared<Tree>(coords, diameter, height));
    }
}

void SnowSceneTile::initOrnaments(){
    for (int i = 0; i < SnowSceneTile::numOrnaments; i++){
        glm::vec3 coords = getRandomPositionOnTile();
        m_sceneObjects.push_back(std::make_shared<Ornament>(coords));
    }
}

void SnowSceneTile::initSnowmen(){
    for (int i = 0; i < SnowSceneTile::numSnowmen; i++){
        float diameterFactor = glm::clamp(Utils::getRandomValue(), .5f, 1.f);
        float diameter = diameterFactor * Snowman::maxDiameter;
        glm::vec3 coords = getRandomPositionOnTile();
        float height = Snowman::computeSnowmanHeight(diameter);
        coords += height / 2.f;
        float speed = SnowSceneObject::getRandomSpeed();
        glm::vec3 direction = SnowSceneObject::getRandomDirection();
        m_sceneObjects.push_back(std::make_shared<Snowman>(coords, diameter, speed, direction));
    }
}

void SnowSceneTile::renderShadowScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    for (int i = 0; i < m_sceneObjects.size(); i++){
        if (context->getCamera()->isVisible(m_sceneObjects[i]->getBoundingBox())){
            m_sceneObjects[i]->renderShadowScene(textures, shader, context, shapes);
        }
    }
}

void SnowSceneTile::renderPhongScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    for (int i = 0; i < m_sceneObjects.size(); i++){
        if (context->getCamera()->isVisible(m_sceneObjects[i]->getBoundingBox())){
            m_sceneObjects[i]->renderPhongScene(textures, shader, context, shapes);
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
