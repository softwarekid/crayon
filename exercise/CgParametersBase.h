#ifndef cgparamters_base__
#define cgparamters_base__
#include <Cg/cg.h>

class CgParametersBase
{
public:
    virtual void BindProgram(CGcontext context, CGprogram program) = 0;
};

#endif
