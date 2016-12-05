#include "tree.h"

Tree::Tree(float height, float radius):
    m_height(height),
    m_radius(radius)
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
    glm::vec3 treePosition = glm::vec3(0, .75f, 0);
    treeTransformation = glm::translate(treeTransformation, treePosition);
    treeTransformation = glm::scale(treeTransformation, glm::vec3(m_radius * 2, .75 * m_height, m_radius * 2));

    m_transformations.push_back(treeTransformation);
}

void Tree::initTreeTrunkPrimitive(){
    CS123ScenePrimitive trunk;
    trunk.type = PrimitiveType::PRIMITIVE_CYLINDER;
    trunk.material.clear();
    trunk.material.cAmbient = glm::vec3(139.f / 255.f, 69.f / 255.f, 19.f / 255.f);
    trunk.material.cDiffuse = glm::vec3(139.f / 255.f, 69.f / 255.f, 19.f / 255.f);
    trunk.material.cSpecular.r = tree.material.cSpecular.g = tree.material.cSpecular.b = 1;
    trunk.material.shininess = 64;

    m_primitives.push_back(trunk);
}

void Tree::initTreeTrunkTransformation(){
    glm::mat4x4 trunkTransformation;
    glm::vec3 trunkPosition = glm::vec3(0, .5f, 0);
    trunkTransformation = glm::translate(trunkTransformation, trunkPosition);
    trunkTransformation = glm::scale(trunkTransformation, glm::vec3(m_radius, .25 * m_height, m_radius));

    m_transformations.push_back(trunkTransformation);
}
