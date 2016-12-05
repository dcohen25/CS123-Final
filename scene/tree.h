#ifndef TREE_H
#define TREE_H

#include "openglsceneobject.h"

class Tree : public OpenGLSceneObject
{
public:
    Tree(float height, float radius);
    ~Tree();

    float getHeight();
    float getRadius();

private:
    void initTree();
    void initTreeTop();
    void initTreeTrunk();
    void initTreeTopPrimitive();
    void initTreeTopTransformation();
    void initTreeTrunkPrimitive();
    void initTreeTrunkTransformation();

    float m_height;
    float m_radius;
};

#endif // TREE_H
