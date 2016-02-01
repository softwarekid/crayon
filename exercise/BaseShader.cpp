#include "BaseShader.h"
#include "CgLog.h"
#include <Cg/cg.h>
#include <CG/cgGL.h>

void BaseShader::_GetProgramParam(CGparameter& param, const char * paramName)
{
    param = cgGetNamedParameter(_program, paramName);
    string error("could not get param");
    error += paramName;
    CgLog::Log(error, _context);
}

void BaseShader::BindProgram()
{
    cgGLBindProgram(_program);
    CgLog::Log("binding program", _context);
}

void BaseShader::LoadProgram()
{
    cgGLLoadProgram(_program);
    CgLog::Log("loading program", _context);
}

void BaseShader::UnloadProgram()
{
    cgGLUnloadProgram(_program);
}

void BaseShader::EnableProfile()
{
    cgGLEnableProfile(_profile);
}

BaseShader::BaseShader(CGcontext context, CGprofile profile, CgParametersBase* params)
{
    this->_context = context;
    this->_profile = profile;
    this->_params = params;
    _program = cgCreateProgram(context, CG_SOURCE, _fileName, profile, _enteryFunName, nullptr);
    CgLog::Log("Creating vertex program", context);
    cgGLLoadProgram(_program);
    CgLog::Log("Loading vertex program", context);
    _params->BindProgram(_context, _program);
}

BaseShader::~BaseShader()
{
    cgDestroyProgram(_program);
}