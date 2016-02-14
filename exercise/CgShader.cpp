#include "CgShader.h"
#include "CgLog.h"
#include <Cg/cg.h>
#include <CG/cgGL.h>

void CgShader::_GetProgramParam(CGparameter& param, const char * paramName)
{
    param = cgGetNamedParameter(_program, paramName);
    string error("could not get param");
    error += paramName;
    CgLog::Log(error, _context);
}

CGcontext CgShader::GetContext() const
{
    return _context;
}

CGprogram CgShader::GetProgram() const
{
    return _program;
}

void CgShader::BindProgram()
{
    cgGLBindProgram(_program);
    CgLog::Log("binding program", _context);
}

void CgShader::LoadProgram()
{
    cgGLLoadProgram(_program);
    CgLog::Log("loading program", _context);
}

void CgShader::UnloadProgram()
{
    cgGLUnloadProgram(_program);
}

void CgShader::EnableProfile()
{
    cgGLEnableProfile(_profile);
}

CgShader::CgShader(CGcontext context, CGprofile profile, const std::string& fileName, const std::string& entry)
{
    this->_context = context;
    this->_profile = profile;
    _program = cgCreateProgram(context, CG_SOURCE, fileName.c_str(), profile, entry.c_str(), nullptr);
    CgLog::Log("Creating vertex program", context);
    cgGLLoadProgram(_program);
    CgLog::Log("Loading vertex program", context);
}

CgShader::~CgShader()
{
    cgDestroyProgram(_program);
}