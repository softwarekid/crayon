#include "VertShader.h"
#include "CgLog.h"
#include <CG/cgGL.h>

VerShader::VerShader(CGcontext context, CGprofile profile, CgParamtersWrapper vertParams): BaseShader(context, profile,vertParams)
{
    _program = cgCreateProgram(context, CG_SOURCE, _fileName, profile, _enteryFunName, nullptr);
    CgLog::Log("Creating vertex program", context);
    cgGLLoadProgram(_program);
    CgLog::Log("Loading vertex program", context);
}