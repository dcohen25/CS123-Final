#include "openglscenetile.h"

OpenGLSceneTile::OpenGLSceneTile(glm::vec3 coords, float tileSize) :
    m_coords(coords),
    m_tileSize(tileSize)
{
}

OpenGLSceneTile::~OpenGLSceneTile(){

}

void OpenGLSceneTile::render(std::unique_ptr<CS123Shader> &shader){
    for (int i = 0; i < m_sceneObjects.size(); i++){
        m_sceneObjects[i].render(shader);
    }
}

void OpenGLSceneTile::setSize(float size){
    m_tileSize = size;
}

void OpenGLSceneTile::setCoords(glm::vec3 coords){
    m_coords = coords;
}

glm::vec3 OpenGLSceneTile::getCoords(){
    return m_coords;
}

float OpenGLSceneTile::getSize(){
    return m_tileSize;
}
