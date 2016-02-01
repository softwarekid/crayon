#ifndef baseShader_h__
#define baseShader_h__
#include <Cg/cg.h>
#include "CgParametersBase.h"

class BaseShader
{
private:
    CGcontext _context;
    CGprofile _profile;

    void _GetProgramParam(CGparameter& param, const char * paramName);

protected:
    CGprogram _program;
    const char* _fileName;
    const char* _enteryFunName;
    CgParametersBase* _params;

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
    BaseShader(CGcontext context, CGprofile profile, CgParametersBase* params);
    virtual ~BaseShader();
};
#endif