#include "BaseShader.h"
#include <Cg/cg.h>
#include <CG/cgGL.h>

void BaseShader::LoadProgram()
{
    cgGLBindProgram(program);
    cglog
}

void BaseShader::UnloadProgram()
{
}

BaseShader::~BaseShader()
{
    cgDestroyProgram(program);
}