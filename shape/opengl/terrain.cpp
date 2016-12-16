#include "terrain.h"
#include "gl/shaders/ShaderAttribLocations.h"

Terrain::Terrain(float width) :
    m_numRows(100),
    m_numCols(m_numRows),
    m_width(width)
{
    render();
}

Terrain::Terrain(const Terrain& terrain) :
    m_numRows(terrain.m_numRows),
    m_numCols(terrain.m_numCols),
    m_width(terrain.m_width)
{
    render();
}

//Terrain::Terrain() :
//    m_numRows(100),
//    m_numCols(m_numRows),
//    m_width(10)
//{
//    render();
//}

Terrain::~Terrain() {

}

/**
 * Returns a pseudo-random value between -1.0 and 1.0 for the given row and column.
 */
float Terrain::randValue(int row, int col) {
    if ((row >= 0 && row <= 1) || (row >= 5 && row <= 6) || (col >= 0 && col <= 1) || (col >= 5 && col <= 6)) {
        return 0;
    }

    return 0.45 * glm::fract(sin(row * 127.1f + col * 311.7f) * 43758.5453123f);
}


/**
 * Returns the object-space position for the terrain vertex at the given row and column.
 */
glm::vec3 Terrain::getPosition(int row, int col) {
    glm::vec3 position;
    position.x = m_width * row/m_numRows - m_width / 2;
    position.y = 0;
    position.z = m_width * col/m_numCols - m_width / 2;

    // TODO: Adjust position.y using value noise.

    for (int i = 0; i < 1; i++) {
        int row_small = row / (20.0 / pow(2, i));
        int col_small = col / (20.0 / pow(2, i));
        float row_fract = glm::fract(row / (20.0 / pow(2, i)));
        float col_fract = glm::fract(col / (20.0 / pow(2, i)));

        float A = randValue(row_small, col_small) / pow(2, i);
        float B = randValue(row_small + 1, col_small) / pow(2, i);
        float C = randValue(row_small, col_small + 1) / pow(2, i);
        float D = randValue(row_small + 1, col_small + 1) / pow(2, i);

        float AB = glm::mix(A, B, row_fract * row_fract * (3-2*row_fract));
        float CD = glm::mix(C, D, row_fract * row_fract * (3-2*row_fract));
        float ABCD = glm::mix(AB, CD, col_fract * col_fract * (3-2*col_fract));

        position.y += ABCD;
    }

    return position;
}


/**
 * Returns the normal vector for the terrain vertex at the given row and column.
 */
glm::vec3 Terrain::getNormal(int row, int col) {
    // TODO: Compute the normal at the given row and column using the positions of the
    //       neighboring vertices.
    std::vector<glm::vec3> vertices;

    glm::vec3 P = getPosition(row, col);

    vertices.push_back(getPosition(row, col + 1) - P);
    vertices.push_back(getPosition(row + 1, col + 1) - P);
    vertices.push_back(getPosition(row + 1, col) - P);
    vertices.push_back(getPosition(row + 1, col - 1) - P);
    vertices.push_back(getPosition(row, col - 1) - P);
    vertices.push_back(getPosition(row - 1, col -1) - P);
    vertices.push_back(getPosition(row - 1, col) - P);
    vertices.push_back(getPosition(row - 1, col + 1) - P);
    vertices.push_back(getPosition(row, col + 1) - P);

    glm::vec3 sum;
    for (int i = 0; i < 8; i++) {
        sum += glm::normalize(glm::cross(vertices.at(i), vertices.at(i + 1)));
    }

    glm::vec3 normal(sum.x / 8.0, sum.y / 8.0, sum.z / 8.0);

    return glm::normalize(normal);
    return glm::vec3(0, 1, 0);
}

void Terrain::tesselate() {
    int numVertices = (m_numRows - 1) * (2 * m_numCols + 2);
//    m_vertices.resize(6 * numVertices);
//    int index = 0;
    glm::vec3 temp;
    for (int row = 0; row < m_numRows - 1; row++) {
        for (int col = m_numCols - 1; col >= 0; col--) {
            temp = getPosition(row, col);
//            m_vertices[index++] = temp.x;
//            m_vertices[index++] = temp.y;
//            m_vertices[index++] = temp.z;
            m_vertices.push_back(temp.x);
            m_vertices.push_back(temp.y);
            m_vertices.push_back(temp.z);
            temp = getNormal  (row, col);
            m_vertices.push_back(temp.x);
            m_vertices.push_back(temp.y);
            m_vertices.push_back(temp.z);
            temp = getPosition(row + 1, col);
            m_vertices.push_back(temp.x);
            m_vertices.push_back(temp.y);
            m_vertices.push_back(temp.z);
            temp = getNormal  (row + 1, col);
            m_vertices.push_back(temp.x);
            m_vertices.push_back(temp.y);
            m_vertices.push_back(temp.z);
        }
        temp = getPosition(row + 1, 0);
        m_vertices.push_back(temp.x);
        m_vertices.push_back(temp.y);
        m_vertices.push_back(temp.z);
        temp = getNormal  (row + 1, 0);
        m_vertices.push_back(temp.x);
        m_vertices.push_back(temp.y);
        m_vertices.push_back(temp.z);
        temp = getPosition(row + 1, m_numCols - 1);
        m_vertices.push_back(temp.x);
        m_vertices.push_back(temp.y);
        m_vertices.push_back(temp.z);
        temp = getNormal  (row + 1, m_numCols - 1);
        m_vertices.push_back(temp.x);
        m_vertices.push_back(temp.y);
        m_vertices.push_back(temp.z);
    }
}

void Terrain::render() {
    tesselate();

    setVertexData(m_vertices.data(), m_vertices.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, m_vertices.size() / 6);
    setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    setAttribute(ShaderAttrib::NORMAL, 3, sizeof(GLfloat)  * 3, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    buildVAO();

//    for (auto i = m_vertices.begin(); i != m_vertices.end(); ++i)
//        std::cout << *i << ' ';
//    std::cout << std::endl;
}
