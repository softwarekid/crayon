#ifndef two_lights_with_struct
#define two_lights_with_struct
#include "GlutWrapper.h"
#include "TwoLightsWithStructVsParam.h"
#include "TwoLightsWithStructFsParam.h"
#include <array>

class TwoLightsWithStruct : public GlutWrapper
{
private:
    TwoLightsWithStructVsParam* _vertParams;
    TwoLightsWithStructFsParam* _fragParams;
    float _lightAngles[2];
    Vector3f _lightColors[2];
    void _SetBrassMaterial();
    void _SetPlasticMaterial();
    void _SetEmissiveOnly(int lightIndex);
protected:
    void _Idle() override;
    void _Display(void) override;
    void _InitVertShader() override;
    void _InitFragShader() override;
    void _InitLightColor();
public:
    TwoLightsWithStruct(const char* title, int width, int height);
};

#endif
