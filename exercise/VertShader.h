#ifndef vertShader_h__
#define vertShader_h__
#include <Cg/cg.h>
#include "BaseShader.h"

class Matrix4f;

class VerShader : public BaseShader
{
private:
    CGparameter MVPMatrix;

public:
    VerShader(CGcontext context, CGprofile profile);
    void SetMVPParam(const Matrix4f _MVPMatrix);
};
#endif