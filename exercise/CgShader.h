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

    //virtual void _OnBindProgram() = 0;
    //virtual void _OnLoadProgram() = 0;
    //virtual void _OnUnloadProgram();
    //virtual void _OnUpdateParam();

    // seperate interface from implementation, anytime you can't
    // decide whether you should provide a default implementation in
    // base class, you'd better not. Because the higher abstraction the
    // class has, the less detail it should contain.
    void InitParams();
public:
    
    CGcontext GetContext() const ;
    CGprogram GetProgram() const ;
    void BindProgram();
    void LoadProgram();
    void UpdateParams();
    void UnloadProgram();
    void EnableProfile();
    void DisableProfile();

    CgShader(CGcontext context, CGprofile profile, const std::string& fileName, const std::string& entry);
    virtual ~CgShader();
};
#endif