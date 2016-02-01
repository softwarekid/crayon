#include "VertShader.h"
#include "CgLog.h"
#include <CG/cgGL.h>

VertShader::VertShader(CGcontext context, CGprofile profile, CgParametersBase vertParams): BaseShader(context, profile,vertParams)
{
    _program = cgCreateProgram(context, CG_SOURCE, _fileName, profile, _enteryFunName, nullptr);
    CgLog::Log("Creating vertex program", context);
    cgGLLoadProgram(_program);
    CgLog::Log("Loading vertex program", context);
    _params.BindProgram(context, _program);
}