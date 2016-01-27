#ifndef baseShader_h__
#define baseShader_h__
#include <Cg/cg.h>

class BaseShader
{
protected:
    CGparameter lightPosition;
    CGparameter eyePosition;
    CGprogram program;
public:
    virtual void UpdateParam();
    virtual ~BaseShader();
};
#endif