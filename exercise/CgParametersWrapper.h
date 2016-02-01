#ifndef cgparamters_wrapper__
#define cgparamters_wrapper__
#include <string>
#include <vector>
using namespace std;

struct BetterCgParam
{
    string name;
    CGparameter param;
};

class CgParamtersWrapper
{
private:
    vector<BetterCgParam> params;
public:
    void AddParams(const string& name);
    void Init(const CGcontext context, const CGprogram program);
};

#endif
