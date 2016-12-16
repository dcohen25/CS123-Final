#include "tree.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include <iostream>

const float Tree::maxDiameter = 1.6f;
const float Tree::maxHeight = 5.f;

const float Tree::topDiameterProportion = 1.f;
const float Tree::trunkDiameterProportion = .2f;
const float Tree::trunkHeightProportion = .3f;
const float Tree::topHeightProportion = .7f;

Tree::Tree(glm::vec3 coords, float diameter, float height):
    SnowSceneObject(coords, diameter, diameter, height),
    m_topDiameter(Tree::topDiameterProportion * diameter),
    m_trunkDiameter(Tree::trunkDiameterProportion * diameter),
    m_trunkHeight(Tree::trunkHeightProportion * height),
    m_topHeight(Tree::topHeightProportion * height)
{
    initTree();
}

Tree::~Tree(){

}


void Tree::renderShadowScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    renderShadowSceneTop(textures, shader, context, shapes);
    renderShadowSceneTrunk(textures, shader, context, shapes);
}

void Tree::renderPhongScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    renderPhongSceneTop(textures, shader, context, shapes);
    renderPhongSceneTrunk(textures, shader, context, shapes);
}

void Tree::renderPhongSceneTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_treeTopTransformation);
    shader->applyMaterial(m_treeTopPrimitive.material);
    shader->setUniform("useTexture", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures.getTreeTopTexture());
    // Set our "renderedTexture" sampler to user Texture Unit 0
    GLuint texID = glGetUniformLocation(shader->getID(), "tex");
    glUniform1i(texID, 1);
    shapes[m_treeTopPrimitive.type]->draw();
    glBindTexture(GL_TEXTURE_2D, 0);
    shader->setUniform("useTexture", 0);
}

void Tree::renderPhongSceneTrunk(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_treeTrunkTransformation);
    shader->applyMaterial(m_treeTrunkPrimitive.material);
    shader->setUniform("useTexture", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures.getTreeTrunkTexture());
    // Set our "renderedTexture" sampler to user Texture Unit 0
    GLuint texID = glGetUniformLocation(shader->getID(), "tex");
    glUniform1i(texID, 1);
    shapes[m_treeTrunkPrimitive.type]->draw();
    glBindTexture(GL_TEXTURE_2D, 0);
    shader->setUniform("useTexture", 0);
}

void Tree::renderShadowSceneTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_treeTopTransformation);
    shapes[m_treeTopPrimitive.type]->draw();
}

void Tree::renderShadowSceneTrunk(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes){
    shader->setUniform("m", m_treeTrunkTransformation);
    shapes[m_treeTrunkPrimitive.type]->draw();
}

void Tree::initTree(){
    initTreeTop();
    initTreeTrunk();
}

void Tree::initTreeTop(){
    initTreeTopPrimitive();
    initTreeTopTransformation();
}

void Tree::initTreeTrunk(){
    initTreeTrunkPrimitive();
    initTreeTrunkTransformation();
}

void Tree::initTreeTopPrimitive(){
    CS123ScenePrimitive tree;
    tree.type = PrimitiveType::PRIMITIVE_CONE;
    tree.material.clear();
    tree.material.cAmbient.g = .1f;
    tree.material.cDiffuse.g = .1f;
    tree.material.cSpecular.r = tree.material.cSpecular.g = tree.material.cSpecular.b = .8;
    tree.material.shininess = 64;

    m_treeTopPrimitive = tree;
}

void Tree::initTreeTopTransformation(){
    glm::mat4x4 treeTransformation;
    treeTransformation = glm::translate(treeTransformation, m_coords);
    treeTransformation = glm::translate(treeTransformation, glm::vec3(0, -m_height / 2 + (m_topHeight * .5) + m_trunkHeight, 0));
    treeTransformation = glm::scale(treeTransformation, glm::vec3(m_topDiameter, m_topHeight, m_topDiameter));

    m_treeTopTransformation = treeTransformation;
}

void Tree::initTreeTrunkPrimitive(){
    CS123ScenePrimitive trunk;
    trunk.type = PrimitiveType::PRIMITIVE_CYLINDER;
    trunk.material.clear();
    trunk.material.cAmbient = glm::vec4(.2f, .1f, .0f, 0);
    trunk.material.cDiffuse = glm::vec4(.2f, .1f, .0f, 0);
    trunk.material.cSpecular.r = trunk.material.cSpecular.g = trunk.material.cSpecular.b = .8;
    trunk.material.shininess = 64;

    m_treeTrunkPrimitive = trunk;
}

void Tree::initTreeTrunkTransformation(){
    glm::mat4x4 trunkTransformation;
    trunkTransformation = glm::translate(trunkTransformation, m_coords);
    trunkTransformation = glm::translate(trunkTransformation, glm::vec3(0, -m_height / 2 + m_trunkHeight * .5, 0));
    trunkTransformation = glm::scale(trunkTransformation, glm::vec3(m_trunkDiameter, m_trunkHeight, m_trunkDiameter));

    m_treeTrunkTransformation = trunkTransformation;
}
