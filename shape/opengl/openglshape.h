#ifndef OPENGLSHAPE_H
#define OPENGLSHAPE_H

#include "GL/glew.h"
#include <memory>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "gl/datatype/VBO.h"
#include "gl/datatype/VBOAttribMarker.h"

namespace CS123 { namespace GL {

class VAO;

}}

using namespace CS123::GL;

class OpenGLShape {

public:
    OpenGLShape();
    virtual ~OpenGLShape();

    /** Draw the initialized geometry. */
    virtual void draw();
    void setVertexData(GLfloat *data, int size, VBO::GEOMETRY_LAYOUT drawMode, int numVertices);
    /** Enables the specified attribute and calls glVertexAttribPointer with the given arguments. */
    void setAttribute(GLuint index, GLuint numElementsPerVertex, int offset, VBOAttribMarker::DATA_TYPE type,
                      bool normalize);
    /** Build the VAO given the specified vertex data and atrributes */
    void buildVAO();

protected:
    std::vector<GLfloat> m_vertices; // vertices
    virtual void render(); // render shape
    void addVertices(glm::vec4 topVertex, glm::vec4 topNormal, glm::vec2 uv);
    virtual void tesselate(){} // Tesselate a shape


private:
    GLfloat *m_data;                            /// vector of floats containing the vertex data.
    GLsizeiptr m_size;                          /// size of the data array, in bytes.
    VBO::GEOMETRY_LAYOUT m_drawMode;            /// drawing mode
    int m_numVertices;                          /// number of vertices to be rendered
    std::vector<VBOAttribMarker> m_markers;     /// list of VBOAttribMarkers that describe how the data is laid out.
    std::unique_ptr<CS123::GL::VAO> m_VAO;      /// a wrapper for the vertex array object (VAO)
    /** Initialize the VBO with the given vertex data. */

};

#endif // SHAPE_H
