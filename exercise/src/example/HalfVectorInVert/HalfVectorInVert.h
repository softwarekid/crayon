#ifndef half_vector_in_vert
#define half_vector_in_vert
#include "GlutWrapper.h"
#include "CgShaderParametersBase.h"
#include "HalfVectorFsParam.h"
#include "HalfVectorVsParam.h"
#include <CG/cgGL.h>

class HalfVectorInVert : public GlutWrapper
{
private:
    float _lightAngle;
    HalfVectorVsParam* _vertParams;
    HalfVectorFsParam* _fragParams;
private:
    void _Idle(void) override;
    void _Reshape(int width, int height) override;
    void _Display(void) override;
    void _InitShaderParams();

protected:
    void _InitVertShader() override;
    void _InitFragShader() override;
public:
    //void StartRendering() override;
    HalfVectorInVert(const char* title, int width, int height, float lightAngle);
    HalfVectorInVert() = delete;
    ~HalfVectorInVert(){}
};

#endif
