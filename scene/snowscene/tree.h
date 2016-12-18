#ifndef TREE_H
#define TREE_H

#include "snowsceneobject.h"

class Tree : public SnowSceneObject
{
public:
    Tree(glm::vec3 coords, float diameter, float height);
    ~Tree();

    virtual void renderPhongScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape> > &shapes) override;
    virtual void renderShadowScene(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape> > &shapes) override;

    float getHeight();
    float getRadius();

    const static float maxDiameter;
    const static float maxHeight;

    const static float topDiameterProportion;
    const static float trunkDiameterProportion;
    const static float trunkHeightProportion;
    const static float topHeightProportion;

    virtual void makeObject() override;

private:
    void initTreeTop();
    void initTreeTrunk();
    void initTreeTopPrimitive();
    void initTreeTopTransformation();
    void initTreeTrunkPrimitive();
    void initTreeTrunkTransformation();

    void renderPhongSceneTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderPhongSceneTrunk(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderShadowSceneTop(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);
    void renderShadowSceneTrunk(SnowSceneTextures textures, std::unique_ptr<CS123Shader> &shader, View *context, std::map<PrimitiveType, std::unique_ptr<OpenGLShape>> &shapes);

    float m_topDiameter;
    float m_trunkDiameter;
    float m_topHeight;
    float m_trunkHeight;

    CS123ScenePrimitive m_treeTopPrimitive;
    CS123ScenePrimitive m_treeTrunkPrimitive;

    glm::mat4x4 m_treeTopTransformation;
    glm::mat4x4 m_treeTrunkTransformation;


};

#endif // TREE_H
