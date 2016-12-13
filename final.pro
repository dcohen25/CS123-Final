# -------------------------------------------------
# Project created by QtCreator 2010-08-22T14:12:19
# -------------------------------------------------
QT += opengl xml
TARGET = final
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14
CONFIG += c++14

unix:!macx {
    LIBS += -lGLU
}
macx {
    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
    QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
    CONFIG += c++11
}
win32 {
    DEFINES += GLEW_STATIC
    LIBS += -lopengl32 -lglu32
}

SOURCES += ui/mainwindow.cpp \
    main.cpp \
    glew-1.10.0/src/glew.c \
    ui/view.cpp \
    ui/viewformat.cpp \
    scene/openglscene.cpp \
    lib/resourceloader.cpp \
    gl/shaders/Shader.cpp \
    gl/GLDebug.cpp \
    gl/textures/Texture.cpp \
    gl/datatype/FBO.cpp \
    gl/datatype/VBO.cpp \
    gl/datatype/VAO.cpp \
    gl/datatype/VBOAttribMarker.cpp \
    gl/shaders/CS123Shader.cpp \
    gl/datatype/IBO.cpp \
    gl/textures/Texture2D.cpp \
    gl/textures/TextureParameters.cpp \
    gl/textures/TextureParametersBuilder.cpp \
    gl/util/FullScreenQuad.cpp \
    gl/shaders/GBufferShader.cpp \
    gl/textures/RenderBuffer.cpp \
    gl/textures/DepthBuffer.cpp \
    shape/opengl/circle.cpp \
    shape/opengl/square.cpp \
    shape/opengl/cone.cpp \
    shape/opengl/cube.cpp \
    shape/opengl/sphere.cpp \
    shape/opengl/cylinder.cpp \
    shape/opengl/openglshape.cpp \
    camera/camtranscamera.cpp \
    scene/snowscene/snowscene.cpp \
    scene/snowscene/snowscenetile.cpp \
    scene/snowscene/tree.cpp \
    scene/utils.cpp \
    scene/snowscene/snowman.cpp \
    scene/snowscene/snow.cpp \
    scene/snowscene/snowsceneobject.cpp \
    scene/boundingbox.cpp \
    soil/image_DXT.c \
    soil/image_helper.c \
    soil/SOIL.c \
    soil/stb_image_aug.c \
    soil/test_SOIL.cpp

HEADERS += ui/mainwindow.h \
    ui_mainwindow.h \
    glew-1.10.0/include/GL/glew.h \
    ui/view.h \
    ui/viewformat.h \
    camera/camera.h \
    scene/openglscene.h \
    lib/resourceloader.h \
    gl/shaders/Shader.h \
    gl/GLDebug.h \
    gl/textures/Texture.h \
    gl/datatype/FBO.h \
    gl/datatype/VBO.h \
    gl/datatype/VAO.h \
    gl/datatype/VBOAttribMarker.h \
    gl/shaders/ShaderAttribLocations.h \
    gl/shaders/CS123Shader.h \
    gl/datatype/IBO.h \
    gl/textures/Texture2D.h \
    gl/textures/TextureParameters.h \
    gl/textures/TextureParametersBuilder.h \
    gl/util/FullScreenQuad.h \
    gl/shaders/GBufferShader.h \
    gl/textures/RenderBuffer.h \
    gl/textures/DepthBuffer.h \
    shape/opengl/circle.h \
    shape/opengl/square.h \
    shape/opengl/cone.h \
    shape/opengl/cube.h \
    shape/opengl/cylinder.h \
    shape/opengl/sphere.h \
    shape/opengl/openglshape.h \
    lib/cs123scenedata.h \
    camera/camtranscamera.h \
    scene/snowscene/snowscene.h \
    scene/snowscene/snowscenetile.h \
    scene/snowscene/tree.h \
    scene/utils.h \
    scene/snowscene/snowman.h \
    scene/snowscene/snow.h \
    scene/snowscene/snowsceneobject.h \
    scene/boundingbox.h \
    soil/image_DXT.h \
    soil/image_helper.h \
    soil/SOIL.h \
    soil/stb_image_aug.h \
    soil/stbi_DDS_aug.h \
    soil/stbi_DDS_aug_c.h

FORMS += ui/mainwindow.ui
INCLUDEPATH += glm ui glew-1.10.0/include
DEPENDPATH += glm ui glew-1.10.0/include

DEFINES += _USE_MATH_DEFINES
DEFINES += TIXML_USE_STL
DEFINES += GLM_SWIZZLE GLM_FORCE_RADIANS
OTHER_FILES += shaders/shader.frag \
    shaders/shader.vert \
    shaders/quad/quad.vert \
    shaders/quad/quad.frag \
    shaders/shadow/shadow.vert \
    shaders/shadow/shadow.frag \
    skybox/front.png \
    skybox/back.png \
    skybox/left.png \
    skybox/right.png \
    skybox/top.png \
    skybox/bottom.png \
    shaders/texture/texture.vert \
    shader/texture/texture.frag

# Don't add the -pg flag unless you know what you are doing. It makes QThreadPool freeze on Mac OS X
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON += -Waddress -Warray-bounds -Wc++0x-compat -Wchar-subscripts -Wformat\
                          -Wmain -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type \
                          -Wsequence-point -Wsign-compare -Wstrict-overflow=1 -Wswitch \
                          -Wtrigraphs -Wuninitialized -Wunused-label -Wunused-variable \
                          -Wvolatile-register-var -Wno-extra

QMAKE_CXXFLAGS += -g

# QMAKE_CXX_FLAGS_WARN_ON += -Wunknown-pragmas -Wunused-function -Wmain

macx {
    QMAKE_CXXFLAGS_WARN_ON -= -Warray-bounds -Wc++0x-compat
}

RESOURCES += \
    resources.qrc

DISTFILES += \
    shaders/normals/normals.vert \
    shaders/normals/normals.frag \
    shaders/normals/normals.gsh \
    shaders/normals/normalsArrow.gsh \
    shaders/normals/normalsArrow.frag \
    shaders/normals/normalsArrow.vert \
    shaders/quad/quad.frag \
    shaders/quad/quad.vert \
    shaders/shadow/shadow.frag \
    shaders/shadow/shadow.vert \
    shaders/skybox/skybox.frag \
    shaders/skybox/skybox.vert \
    shaders/texture/texture.frag
