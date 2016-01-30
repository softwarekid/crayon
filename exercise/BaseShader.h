#ifndef baseShader_h__
#define baseShader_h__
#include <Cg/cg.h>

class BaseShader
{
protected:
    CGparameter lightPosition;
    CGparameter eyePosition;
    CGprogram program;

    virtual void OnLoadProgram();
    virtual void OnUnloadProgram();
    virtual void OnUpdateParam();
public:
    void LoadProgram();
    void UnloadProgram();
    void UpdateParam();
    virtual ~BaseShader();
};
#endif