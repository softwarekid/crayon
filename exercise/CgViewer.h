#ifndef cg_viewer_h__
#define cg_viewer_h__
#include "GlutWrapper.h"
#include <Cg/cg.h>

class CgViewer : public GlutWrapper
{
private:
    CGcontext _context;
    float _lightAngle;

private:
    void _Keyboard(int c, int x, int y) override;
    void _Idle(void) override;
    void _Reshape(int width, int height) override;
    void _Display(void) override;
    void _Menu() override;
    void _Init();
    
    CgShaderParametersBase* vertParam;
    CgShaderParametersBase* fragParam;
protected:
    void InitVertShader() override;
    void InitFragShader() override;
public:
    void StartRendering();
    CgViewer(const char* title, int width, int height, float lightAngle);
    ~CgViewer(){}
};

#endif
