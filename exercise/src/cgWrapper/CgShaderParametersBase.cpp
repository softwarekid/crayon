#include "CgShaderParametersBase.h"
#include "CgLog.h"
#include <CG/cgGL.h>

void CgShaderParametersBase::_GetProgramParam(CGparameter& param, const char* name)
{
    param = cgGetNamedParameter(_program, name);
    string error("could not get param ");
    error += name;
    CgLog::Log(error, _context);
}

void CgShaderParametersBase::_Set3fvParam(const CGparameter param, const Vector3f& value)
{
    float valueAdaptor[3] = {value.x, value.y, value.z};
    cgSetParameter3fv(param, valueAdaptor);
    CgLog::Log("set 3fv param", _context);
}

void CgShaderParametersBase::_Set1fParam(const CGparameter param, const float value)
{
    cgSetParameter1f(param, value);
    CgLog::Log("set 1f param", _context);
}

void CgShaderParametersBase::_Set2fParam(const CGparameter param, float value1, const float value2)
{
    cgSetParameter2f(param, value1, value2);
    CgLog::Log("set 2f param", _context);
}

void CgShaderParametersBase::_SetTextureParam(const CGparameter param, const GLuint name)
{
    cgGLSetTextureParameter(param, name);
    CgLog::Log("set texture param", _context);
}

void CgShaderParametersBase::_setMatrix4fParam(const CGparameter param, const Matrix4f& value)
{
    float innerValue[16];
    value.GetInnerValue(innerValue);
    cgSetMatrixParameterfr(param, innerValue);
    CgLog::Log("set matrix4f param", _context);
}

CgShaderParametersBase::CgShaderParametersBase(const CgShader& shader)
{
    _context = shader.GetContext();
    _program = shader.GetProgram();
}

CgShaderParametersBase::CgShaderParametersBase(CGcontext context, CGprogram program)
{
    _context = context;
    _program = program;
}