#include "CgProgram.h"
#include <CG/cgGL.h>


Vector3f CgProgram::_MatVecMulReduced(const Matrix4f& matrix, const Vector4f& vector)
{
    auto result = matrix.Mul(vector);
    result.ReduceTo3DSpace();
    return Vector3f(result[1], result[2], result[3]);
}

CgProgram::CgProgram(CGcontext content, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry)
{
    auto profileVert = cgGLGetLatestProfile(CG_GL_VERTEX);
    _vertShader = new CgShader(content, profileVert, vertFileName, vertEntry);
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    _fragShader = new CgShader(content, profileFrag, fragFilename, fragEntry);
}

CgProgram::~CgProgram()
{
    // maybe I can use unique_ptr
    delete _vertShader;
    _vertShader = nullptr;
    delete _fragShader;
    _fragShader = nullptr;
}