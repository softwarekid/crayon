#include "BaseShader.h"
#include "CgLog.h"
#include <Cg/cg.h>
#include <CG/cgGL.h>

void BaseShader::_GetProgramParam(CGparameter param, const char * paramName)
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

BaseShader::BaseShader(CGcontext context, CGprofile profile, CgParamtersWrapper params)
{
    this->_context = context;
    this->_profile = profile;
    this->_params = params;
    this->_params.Init();
}

BaseShader::~BaseShader()
{
    cgDestroyProgram(_program);
}