#include "VertShader.h"
#include "CgLog.h"
#include <CG/cgGL.h>

VerShader::VerShader(CGcontext context, CGprofile profile): BaseShader(context, profile)
{
    _program = cgCreateProgram(context, CG_SOURCE, _fileName, profile, _enteryFun, nullptr);
    CgLog::Log("Creating vertex program", context);
    cgGLLoadProgram(_program);
    CgLog::Log("Loading vertex program", context);

}