#ifndef cg_viewer_h__
#define cg_viewer_h__
#include "GlutWrapper.h"
class CgViewer : public GlutWrapper
{
private:
    bool _isAnimating;
    CGprogram vertexProgarm;
    CGprogram fragProgarm;

private:
    void _Draw() override;
    void _Keyboard(int c, int x, int y) override;
    void _Idle(void) override;
    void _Reshape(int width, int height) override;
    void _Display(void) override;
    void _Menu() override;

public:
    CgViewer(const char* title, int width, int height, float lightAngle, bool isAnimating);
    ~CgViewer()
    {
        
    }
};



#endif
