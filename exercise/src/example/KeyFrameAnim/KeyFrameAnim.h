#ifndef key_frame_anim__
#define key_frame_anim__
#include "GlutWrapper.h"
#include "KnightDrawCall.h"
#include "tga_c_loader/md2.h"
#include "tga_c_loader/md2render.h"
#include "tga_c_loader/loadtex.h"

class KeyFrameAnim : public GlutWrapper
{
private:
    float _lightAngle;
    GLuint name;
    const std::string _animVertShaderName = R"(src\example\KeyFrameAnim\AnimationLit_F.cg)";
    const std::string _animFragShaderName = R"(src\example\KeyFrameAnim\AnimationLit_V.cg)";
    const std::string _vertEntry = R"(main_v)";
    const std::string _fragEntry = R"(main_f)";

    KnightDrawCall* _knightDrawCall;
    Md2Model* _myKnightModel;
    MD2render* _myMD2render;
    float _myFrameKnob = 0;

private:
    float _AddDeltaFrame(float baseFrameKnob, float delta);
protected:
    void _Idle() override;
    void _Display(void) override;
    void _LoadModelAndTexture();

public:
    KeyFrameAnim(const char* title, int width, int height );
    KeyFrameAnim() = delete;
    ~KeyFrameAnim();
};

#endif