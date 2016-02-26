#ifndef cgparamters_base__
#define cgparamters_base__
#include <Cg/cg.h>
#include <Matrix.h>
#include <GL/glew.h>
#include "CgShader.h"

class CgShaderParametersBase
{
private:
    CGcontext _context;
    CGprogram _program;
protected:

    void _GetProgramParam(CGparameter& param, const char * name);
    void _Set3fvParam(const CGparameter param, const Vector3f& value);
    void _Set1fParam(const CGparameter param, const float value);
    void _SetTextureParam(const CGparameter paaram, const GLuint name);
    void _setMatrix4fParam(const CGparameter param, const Matrix4f & value);
public:
    virtual void ExtractParams() {};
    virtual ~CgShaderParametersBase(){};

public:
    explicit CgShaderParametersBase(const CgShader& shader);
    CgShaderParametersBase(CGcontext context, CGprogram program);
    CgShaderParametersBase(){};
};

#endif