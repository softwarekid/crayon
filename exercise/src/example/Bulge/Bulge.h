#ifndef bulge_h__
#define  bulge_h__
#include "GlutWrapper.h"
#include "BulgeVsParam.h"
#include "BulgeFsParam.h"
class Bulge : public GlutWrapper
{
private:
    BulgeVsParam* _vertParams;
    BulgeFsParam* _fragParams;

protected:
    void _Idle() override;
    void _Display(void) override;
    void _InitVertShader() override;
    void _InitFragShader() override;

    Bulge(const char* title, int width, int height);
};


#endif