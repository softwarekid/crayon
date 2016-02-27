#ifndef two_lights_with_struct
#define two_lights_with_struct
#include "GlutWrapper.h"
#include "TwoLightsWithStructVsParam.h"
class TwoLightsWithStruct : public GlutWrapper
{
private:
    void _Display(void) override;
    void _InitShaderParams() override;
    TwoLightsWithStructVsParam* _vertParams;
protected:
    void _InitVertShader() override;
    void _InitFragShader() override;
public:
    TwoLightsWithStruct(const char* title, int width, int height);
};

#endif
