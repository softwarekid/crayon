#ifndef texture_sampling
#define texture_sampling
#include "GlutWrapper.h"
class TextureSampling : public GlutWrapper
{
private:
    void _Reshape(int width, int height) override;
    void _Display(void) override;
    void _InitShaderParams() override;
    const GLubyte* _texture;
protected:
    void _InitVertShader() override;
    void _InitFragShader() override;
public:
    TextureSampling(const char* title, int width, int height, const GLubyte* texture );
    TextureSampling() = delete;
    ~TextureSampling(){}
};

#endif
