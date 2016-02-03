#ifndef frag_shader_param__
#define frag_shader_param__
#include "CgShaderParametersBase.h"
class FragShaderParam : public CgShaderParametersBase
{
    void BindProgram(CGcontext context, CGprogram program) override;
};
#endif
