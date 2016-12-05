#ifndef TREE_H
#define TREE_H

#include "snowsceneobject.h"

class Tree : public SnowSceneObject
{
public:
    Tree(glm::vec3 coords, float diameter, float height);
    ~Tree();

    float getHeight();
    float getRadius();

    const static float maxDiameter;
    const static float maxHeight;
    const static float topDiameterProportion;
    const static float trunkDiameterProportion;
    const static float trunkHeightProportion;
    const static float topHeightProportion;

private:
    void initTree();
    void initTreeTop();
    void initTreeTrunk();
    void initTreeTopPrimitive();
    void initTreeTopTransformation();
    void initTreeTrunkPrimitive();
    void initTreeTrunkTransformation();

    float m_topDiameter;
    float m_trunkDiameter;
    float m_topHeight;
    float m_trunkHeight;
};

#endif // TREE_H
