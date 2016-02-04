#ifndef cgparamters_base__
#define cgparamters_base__
#include <Cg/cg.h>
#include "Matrix.h"

class CgShaderParametersBase
{
private:
    CGcontext _context;
    CGprogram _program;
protected:
    void _GetProgramParam(CGparameter& param, const char * name);
    void _Set3fvParam(const CGparameter param, const Vector3f& value);
    void _Set1fParam(const CGparameter param, const float value);
    void _setMatrix4fParam(const CGparameter param, const Matrix4f & value);
public:
    virtual void SetMVPMatrix(const Matrix4f& value);
    virtual void SetKeCoef(const Vector3f& value);
    virtual void SetKaCoef(const Vector3f& value);
    virtual void SetKdCoef(const Vector3f& value);
    virtual void SetKsCoef(const Vector3f& value);
    virtual void SetShinessCoef(const float value);

    virtual void Init() = 0;
    virtual ~CgShaderParametersBase(){};

public:
    CgShaderParametersBase(CGcontext context, CGprogram program);
};

#endif