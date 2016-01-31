#include "BaseShader.h"
#include "CgLog.h"
#include <Cg/cg.h>
#include <CG/cgGL.h>

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

BaseShader::BaseShader(CGcontext context, CGprofile profile)
{
    this->_context = context;
    this->_profile = profile;
}

BaseShader::~BaseShader()
{
    cgDestroyProgram(_program);
}