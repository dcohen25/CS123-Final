#ifndef FULLSCREENQUAD_H
#define FULLSCREENQUAD_H

#include <memory>
#include "gl/datatype/VBO.h"
#include "gl/datatype/VBOAttribMarker.h"
#include "gl/datatype/VAO.h"

namespace CS123 { namespace GL {

class VAO;

}}

using namespace CS123::GL;

class FullScreenQuad {
public:
    FullScreenQuad();

    void draw();

private:
    std::unique_ptr<CS123::GL::VAO> m_vao;
};

#endif // FULLSCREENQUAD_H
