#ifndef two_texture_access__
#define two_texture_access__
#include <GlutWrapper.h>
#include "TwoTextureAccessFsParam.h"
#include "TwoTextureAccessVsParam.h"

class TwoTextureAccess :public GlutWrapper
{
private:
    float seperation = 0.1f;
    float seperationVelocity = 0.005f;
    void _Idle() override;
    void _Display(void) override;
    void _InitShaderParams();
    const GLubyte* _texture;
    TwoTextureAccessVsParam* _vertParams;
    TwoTextureAccessFsParam* _fragParams;
protected:
    void _InitVertShader() override;
    void _InitFragShader() override;
public:
    TwoTextureAccess(const char* title, int width, int height, const GLubyte* texture );
    TwoTextureAccess() = delete;
    ~TwoTextureAccess(){}
};


#endif
