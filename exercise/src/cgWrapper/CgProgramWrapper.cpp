#include "CgProgramWrapper.h"
#include <CG/cgGL.h>
#include <string>


Vector3f CgProgramWrapper::_MatVecMulReduced(const Matrix4f& matrix, const Vector4f& vector)
{
    auto result = matrix.Mul(vector);
    result.ReduceTo3DSpace();
    return Vector3f(result[1], result[2], result[3]);
}

void CgProgramWrapper::BindShader()
{
    _vertShader->BindProgram();
    _fragShader->BindProgram();
}

void CgProgramWrapper::EnableProfile()
{
    _vertShader->EnableProfile();
    _fragShader->EnableProfile();
}

void CgProgramWrapper::DisableProfile()
{
    _vertShader->DisableProfile();
    _fragShader->DisableProfile();
}

void CgProgramWrapper::SetProjection(float fov, float aspectRatio, float zNear, float zFar)
{
    _transform.SetProjection(fov, aspectRatio, zNear, zFar);
}

CgProgramWrapper::CgProgramWrapper(CGcontext content, CGprofile vertProfile, CGprofile fragProfile,std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry)
{
    _vertShader = new CgShader(content, vertProfile, vertFileName, vertEntry);
    _fragShader = new CgShader(content, fragProfile, fragFilename, fragEntry);
}

CgProgramWrapper::~CgProgramWrapper()
{
    // maybe I can use unique_ptr
    delete _vertShader;
    _vertShader = nullptr;
    delete _fragShader;
    _fragShader = nullptr;
}