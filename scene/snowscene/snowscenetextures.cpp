#include "snowscenetextures.h"

#include <QGLWidget>

SnowSceneTextures::SnowSceneTextures()
{
    initTextures();

}

SnowSceneTextures::~SnowSceneTextures(){

}

void SnowSceneTextures::initTextures(){
    initTreeTopTexture();
    initTreeTrunkTexture();
    initSnowmanTopTexture();
}

GLuint SnowSceneTextures::getTreeTopTexture(){
    return m_treeTopTexture;
}

GLuint SnowSceneTextures::getTreeTrunkTexture(){
    return m_treeTrunkTexture;
}

GLuint SnowSceneTextures::getSnowmanTopTexture(){
    return m_snowmanTopTexture;
}

void SnowSceneTextures::initSnowmanTopTexture(){
    QImage image(":/images/snowman-face.jpg");
    // generate texture
    glGenTextures(1, &m_snowmanTopTexture);
    // bind texture
    glBindTexture(GL_TEXTURE_2D, m_snowmanTopTexture);
    // send image data to the bound texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image.bits());
    // set parameteri
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}


void SnowSceneTextures::initTreeTopTexture(){
    // TODO (Task 6): Initialize texture map.
   QImage image(":/images/tree-top.jpg");
   // generate texture
   glGenTextures(1, &m_treeTopTexture);
   // bind texture
   glBindTexture(GL_TEXTURE_2D, m_treeTopTexture);
   // send image data to the bound texture
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image.bits());
   // set parameteri
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   // unbind texture
   glBindTexture(GL_TEXTURE_2D, 0);
}

void SnowSceneTextures::initTreeTrunkTexture(){
    // TODO (Task 6): Initialize texture map.
   QImage image(":/images/tree-bark.jpg");
   // generate texture
   glGenTextures(1, &m_treeTrunkTexture);
   // bind texture
   glBindTexture(GL_TEXTURE_2D, m_treeTrunkTexture);
   // send image data to the bound texture
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image.bits());
   // set parameteri
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   // unbind texture
   glBindTexture(GL_TEXTURE_2D, 0);
}
