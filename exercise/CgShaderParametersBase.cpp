#include "CgShaderParametersBase.h"
#include "CgLog.h"

void CgShaderParametersBase::_GetProgramParam(CGcontext context, CGprogram program, CGparameter& param, const char * name)
{
    param = cgGetNamedParameter(program, name);
    std::string error("could not get param");
    error += name;
    CgLog::Log(error, context);
}

void CgShaderParametersBase::_Set3fvParam(const CGparameter param, const Vector3f& value)
{
    float valueAdaptor[3] = {value.x, value.y, value.z};
    cgSetParameter3fv(param, valueAdaptor);
}

void CgShaderParametersBase::_Set1fParam(const CGparameter param, const float value)
{
    cgSetParameter1f(param, value);
}

void CgShaderParametersBase::_setMatrix4fParam(const CGparameter param, const Matrix4f& value)
{
    float innerValue[16];
    value.GetInnerValue(innerValue);
    cgSetMatrixParameterfr(param, innerValue);
}

CgShaderParametersBase::CgShaderParametersBase(CGcontext context, CGprogram program)
{
    _context = context;
    _program = program;
}

