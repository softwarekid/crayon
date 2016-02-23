#ifndef CgLog_h__
#define CgLog_h__
#include <string>
#include <Cg/cg.h>
using namespace std;
class CgLog
{
public:
    void static Log(string situation, CGcontext context);
};

#endif