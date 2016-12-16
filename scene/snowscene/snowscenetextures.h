#ifndef SNOWSCENETEXTURES_H
#define SNOWSCENETEXTURES_H

#include "gl/gl.h"

class SnowSceneTextures
{
public:
    SnowSceneTextures();
    ~SnowSceneTextures();

    GLuint getTreeTopTexture();
    GLuint getTreeTrunkTexture();
    GLuint getSnowmanTopTexture();

private:
    void initTextures();
    void initTreeTopTexture();
    void initTreeTrunkTexture();
    void initSnowmanTopTexture();

    GLuint m_treeTopTexture;
    GLuint m_treeTrunkTexture;
    GLuint m_snowmanTopTexture;
};

#endif // SNOWSCENETEXTURES_H
