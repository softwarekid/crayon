#ifndef key_frame_anim__
#define key_frame_anim__
#include "GlutWrapper.h"

class KeyFrameAnim : GlutWrapper
{
private:
    float _lightAngle;
    
protected:
    void _Idle() override;
    void _Display(void) override;

public:
    KeyFrameAnim(const char* title, int width, int height, float lightAngle);
    KeyFrameAnim() = delete;
    ~KeyFrameAnim();
};

#endif