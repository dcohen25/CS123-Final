#include "tree.h"

Tree::Tree()
{
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

void SnowSceneTile::initTreePrimitives(){
    for (int i = 0; i < m_numTrees; i++){
        CS123ScenePrimitive tree = makeTree();
        m_primitives.push_back(tree);
    }
}

void SnowSceneTile::initTreeTransformations(){
    for (int i = 0; i < m_numTrees; i++){
        glm::mat4x4 transformation = computeTreeTransformation();
        m_transformations.push_back(transformation);
    }
}

glm::mat4x4 SnowSceneTile::computeTreeTransformation(){
    glm::mat4x4 treeTransformation;
    glm::vec3 treePosition = getRandomObjectPosition();
    treePosition.y += .5f;
    treeTransformation = glm::translate(treeTransformation, treePosition);
    return treeTransformation;
}
