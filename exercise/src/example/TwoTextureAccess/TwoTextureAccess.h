#ifndef two_texture_access__
#define two_texture_access__
#include <GlutWrapper.h>

class TwoClassAccess :public GlutWrapper
{
private:
    void _Display(void) override;
    void _InitShaderParams() override;
    const GLubyte* _texture;
protected:
    void _InitVertShader() override;
    void _InitFragShader() override;
public:
    TwoClassAccess(const char* title, int width, int height, const GLubyte* texture );
    TwoClassAccess() = delete;
    ~TwoClassAccess(){}
};


#endif
