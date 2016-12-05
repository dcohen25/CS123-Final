#include "tree.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"


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
    tree.material.cAmbient.g = .3f;
    tree.material.cDiffuse.g = 1.f;
    tree.material.cSpecular.r = tree.material.cSpecular.g = tree.material.cSpecular.b = 1;
    tree.material.shininess = 64;

    m_primitives.push_back(tree);
}

void Tree::initTreeTopTransformation(){
    glm::mat4x4 treeTransformation;
    treeTransformation = glm::translate(treeTransformation, m_coords);
    treeTransformation = glm::translate(treeTransformation, glm::vec3(0, -m_height / 2 + (m_topHeight * .5) + m_trunkHeight, 0));
    treeTransformation = glm::scale(treeTransformation, glm::vec3(m_topDiameter, m_topHeight, m_topDiameter));

    m_transformations.push_back(treeTransformation);
}

void Tree::initTreeTrunkPrimitive(){
    CS123ScenePrimitive trunk;
    trunk.type = PrimitiveType::PRIMITIVE_CYLINDER;
    trunk.material.clear();
    trunk.material.cAmbient = glm::vec4(.3f, .2f, .1f, 0);
    trunk.material.cDiffuse = glm::vec4(.3f, .2f, .1f, 0);
    trunk.material.cSpecular.r = trunk.material.cSpecular.g = trunk.material.cSpecular.b = 1;
    trunk.material.shininess = 64;

    m_primitives.push_back(trunk);
}

void Tree::initTreeTrunkTransformation(){
    glm::mat4x4 trunkTransformation;
    trunkTransformation = glm::translate(trunkTransformation, m_coords);
    trunkTransformation = glm::translate(trunkTransformation, glm::vec3(0, -m_height / 2 + m_trunkHeight * .5, 0));
    trunkTransformation = glm::scale(trunkTransformation, glm::vec3(m_trunkDiameter, m_trunkHeight, m_trunkDiameter));

    m_transformations.push_back(trunkTransformation);
}
