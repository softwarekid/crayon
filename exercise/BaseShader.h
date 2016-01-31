#ifndef baseShader_h__
#define baseShader_h__
#include <Cg/cg.h>
#include <string>

class BaseShader.l
{
private:
    CGcontext _context;
    CGprofile _profile;


protected:
    CGprogram _program;
    const char* _fileName;
    const char* _enteryFun;

    virtual void OnBindProgram();
    virtual void OnLoadProgram();
    virtual void OnUnloadProgram();
    virtual void OnUpdateParam();
    virtual void 
public:
    void BindProgram();
    void LoadProgram();
    void UnloadProgram();
    void EnableProfile();


    void UpdateParam();
    BaseShader(CGcontext context, CGprofile profile);
    virtual ~BaseShader();
};
#endif