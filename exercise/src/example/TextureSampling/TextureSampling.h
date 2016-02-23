#ifndef texture_sampling
#define texture_sampling
#include "GlutWrapper.h"
class TextureSampling : public GlutWrapper
{
private:
    float _lightAngle;
private:
    void _Reshape(int width, int height) override;
    void _Display(void) override;
    void _InitShaderParams();

protected:
    void _InitVertShader() override;
    void _InitFragShader() override;
public:
    void StartRendering();
    TextureSampling(const char* title, int width, int height, float lightAngle);
    TextureSampling() = delete;
    ~TextureSampling(){}
};

#endif
