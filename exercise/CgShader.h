#ifndef CgShader_h__
#define CgShader_h__
#include <Cg/cg.h>
#include "CgShaderParametersBase.h"
#include <string>

class CgShader
{
private:
    CGcontext _context;
    CGprofile _profile;

    void _GetProgramParam(CGparameter& param, const char * paramName);

protected:
    CGprogram _program;
    CgShaderParametersBase* _params;

    //virtual void _OnBindProgram() = 0;
    //virtual void _OnLoadProgram() = 0;
    //virtual void _OnUnloadProgram();
    //virtual void _OnUpdateParam();

    // seperate interface from implementation, anytime you can't
    // decide whether you should _entry_entry_entryprovide a default implementation in
    // base class, you'd better not. Because the higher abstraction the
    // class has, the less detail it should contain.
    void InitParams();
public:
    void BindProgram();
    void LoadProgram();
    void UnloadProgram();
    void EnableProfile();

    void UpdateParam();
    CgShader(CGcontext context, CGprofile profile, const std::string& fileName, const std::string& entry, CgShaderParametersBase* params);
    virtual ~CgShader();
};
#endif