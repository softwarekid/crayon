#include "CgParametersWrapper.h"
#include <Cg/cg.h>
#include "CgLog.h"

void CgParamtersWrapper::AddParams(const string& name)
{
    BetterCgParam param = {name, nullptr};
    params.push_back(param);
}

void CgParamtersWrapper::Init(const CGcontext context, const CGprogram program)
{
    for(int i = 0; i < params.size(); i++)
    {
        params[i].param = cgGetNamedParameter(program, params[i].name.c_str());
        string error("could not get param");
        error += params[i].name;
        CgLog::Log(error, context);
    }
}
