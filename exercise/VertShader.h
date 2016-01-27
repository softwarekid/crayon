#ifndef vertShader_h__
#define vertShader_h__
#include <Cg/cg.h>
#include "BaseShader.h"
#include "FragmentShader.h"

class Matrix4f;

class VerShader : public BaseShader
{
private:
    CGparameter MVPMatrix;


public:
    void SetMVPParam(const Matrix4f _MVPMatrix);
};
#endif