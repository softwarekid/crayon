#ifndef cgparamters_base__
#define cgparamters_base__
#include <Cg/cg.h>
#include "Matrix.h"
class CgShaderParametersBase
{
public:
    virtual void SetMVPMatrix(CGparameter param, Matrix4f value);
    virtual void SetKdCoef(CGparameter param, Vector3f value);
    virtual void BindProgram(CGcontext context, CGprogram program) = 0;
    virtual ~CgShaderParametersBase(){};
};

#endif
