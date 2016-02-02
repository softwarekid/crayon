#ifndef vert_param__
#define vert_param__
#include "CgShaderParametersBase.h"

class VertShaderParam:public CgShaderParametersBase
{
private:
    CGparameter MVP;
    

public:
    VertShaderParam();
    void BindProgram(CGcontext context, CGprogram program) override;
};
#endif