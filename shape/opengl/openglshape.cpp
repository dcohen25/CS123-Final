#include "shape/opengl/openglshape.h"

#include "gl/datatype/VAO.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include "glm/glm.hpp"
#include "gl/shaders/CS123Shader.h"
#include "gl/shaders/Shader.h"
#include "resourceloader.h"

using namespace CS123::GL;

OpenGLShape::OpenGLShape() :
    m_size(0),
    m_drawMode(VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES),
    m_numVertices(0),
    m_VAO(nullptr)
{
    // You shouldn't need to do anything here
    // Aren't initializer lists amazing?
}

OpenGLShape::~OpenGLShape()
{
    // You shouldn't need to do anything here
    // m_VAO's destructor will automatically be called
    // Aren't smart pointers amazing?
}

// render shape
void OpenGLShape::render(){
    tesselate();
    setVertexData(m_vertices.data(), m_vertices.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, m_vertices.size() / 6);
    setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(ShaderAttrib::NORMAL, 3, sizeof(float) * 3, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    buildVAO();
}

// add vertices
void OpenGLShape::addVertices(glm::vec4 topVertex, glm::vec4 topNormal, glm::vec4 leftVertex, glm::vec4 leftNormal, glm::vec4 rightVertex, glm::vec4 rightNormal){
    // top vertex
    m_vertices.push_back(topVertex[0]);
    m_vertices.push_back(topVertex[1]);
    m_vertices.push_back(topVertex[2]);
    // top normal
    m_vertices.push_back(topNormal[0]);
    m_vertices.push_back(topNormal[1]);
    m_vertices.push_back(topNormal[2]);
    // left vertex
    m_vertices.push_back(leftVertex[0]);
    m_vertices.push_back(leftVertex[1]);
    m_vertices.push_back(leftVertex[2]);
    // left normal
    m_vertices.push_back(leftNormal[0]);
    m_vertices.push_back(leftNormal[1]);
    m_vertices.push_back(leftNormal[2]);
    // right vertex
    m_vertices.push_back(rightVertex[0]);
    m_vertices.push_back(rightVertex[1]);
    m_vertices.push_back(rightVertex[2]);
    // right normal
    m_vertices.push_back(rightNormal[0]);
    m_vertices.push_back(rightNormal[1]);
    m_vertices.push_back(rightNormal[2]);
}

/**
 * @param data - Vector of floats containing the vertex data.
 * @param size - number of elements in the array.
 * @param drawMode - Drawing mode
 * @param numVertices - Number of vertices to be rendered.
 */
void OpenGLShape::setVertexData(GLfloat *data, int size, VBO::GEOMETRY_LAYOUT drawMode, int numVertices) {
    // Store the vertex data and other values to be used later when constructing the VAO
    m_data = data;
    m_size = size;
    m_drawMode = drawMode;
    m_numVertices = numVertices;
}

/**
 * @param name OpenGL handle to the attribute location. These are specified in ShaderAttribLocations.h
 * @param numElementsPerVertex Number of elements per vertex. Must be 1, 2, 3 or 4 (e.g. position = 3 for x,y,z)
 * @param offset Offset in BYTES from the start of the array to the beginning of the first element
 * @param type Primitive type (FLOAT, INT, UNSIGNED_BYTE)
 * @param normalize
 */
void OpenGLShape::setAttribute(
         GLuint name, GLuint numElementsPerVertex, int offset, VBOAttribMarker::DATA_TYPE type, bool normalize) {
    m_markers.push_back(VBOAttribMarker(name, numElementsPerVertex, offset, type, normalize));
}

void OpenGLShape::buildVAO() {
    CS123::GL::VBO vbo = VBO(m_data, m_size, m_markers, m_drawMode);
    m_VAO = std::make_unique<VAO>(vbo, m_numVertices);
}

void OpenGLShape::draw() {
    if (m_VAO) {
        // TODO [Task 5]
        m_VAO->bind();
        m_VAO->draw();
    }
}
