#ifndef vertShader_h__
#define vertShader_h__
#include <Cg/cg.h>
#include "BaseShader.h"
#include "CgParametersWrapper.h"

class Matrix4f;

class VerShader : public BaseShader
{
private:
public:
    void _InitParams();
    VerShader(CGcontext context, CGprofile profile, CgParamtersWrapper VertParams);
};
#endif