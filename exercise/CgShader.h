#ifndef CgShader_h__
#define CgShader_h__
#include <Cg/cg.h>
#include "CgShaderParametersBase.h"

class CgShader
{
private:
    CGcontext _context;
    CGprofile _profile;

    void _GetProgramParam(CGparameter& param, const char * paramName);

protected:
    CGprogram _program;
    const char* _fileName;
    const char* _enteryFunName;
    CgShaderParametersBase* _params;

    //virtual void _OnBindProgram() = 0;
    //virtual void _OnLoadProgram() = 0;
    //virtual void _OnUnloadProgram();
    //virtual void _OnUpdateParam();

    // seperate interface and implementation, anytime when you can't
    // decide whether you should provide a default implementation in
    // base class, you'd better not. Because the higher abstraction the
    // class has, the less detail it should contain.
    void InitParams();
public:
    void BindProgram();
    void LoadProgram();
    void UnloadProgram();
    void EnableProfile();

    void UpdateParam();
    CgShader(CGcontext context, CGprofile profile, CgShaderParametersBase* params);
    virtual ~CgShader();
};
#endif