#include "BaseShader.h"
#include <Cg/cg.h>

BaseShader::~BaseShader()
{
    cgDestroyProgram(program);
}