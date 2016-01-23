#ifndef vertShader_h__
#define vertShader_h__
#include <Cg/cg.h>
#include "BaseShader.h"

class VerShader : public BaseShader
{
private:
    CGparameter MVPMatrix;


public:
    void SetMVPParam(const Matrix4f _MVPMatrix);
};
#endif