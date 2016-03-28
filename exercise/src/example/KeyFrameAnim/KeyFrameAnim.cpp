#include "KeyFrameAnim.h"
#include <CG/cgGL.h>
#include <CgLog.h>
#include <iostream>

void KeyFrameAnim::_Idle()
{
}

void KeyFrameAnim::_Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Vector3f eyePosition(0, 0, 13);
    const Vector3f eyeCenter(0, 0, 0);
    const Vector3f eyeUp(0, 1, 0);
    const Vector3f lightPosition(5 * sin(_lightAngle), 1.5, 5 * cos(_lightAngle));

    _knightDrawCall->BindShader();
    _knightDrawCall->EnableProfile();
    _knightDrawCall->SetConstParams();
    _knightDrawCall->SetVaringParams();
}

void KeyFrameAnim::_LoadModelAndTexture()
{
    _myKnightModel = md2ReadModel("knight.md2");
    if (0 == _myKnightModel) 
    {
        cout << "load model failure\n";
        exit(1);
    }
    _myMD2render = createMD2render(_myKnightModel);
    gliGenericImage *decalImage;
    decalImage = readImage("knight.tga");
    glGenTextures(1, &name);
    glBindTexture(GL_TEXTURE_2D, name);
    decalImage = loadTextureDecal(decalImage, 1);
    gliFree(decalImage);
}

KeyFrameAnim::KeyFrameAnim(const char* title, int width, int height, float lightAngle) : GlutWrapper(title, width, height)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    _context = cgCreateContext();
    CgLog::Log("create content", _context);
    cgGLSetDebugMode(CG_TRUE);
    cgSetParameterSettingMode(_context,CG_DEFERRED_PARAMETER_SETTING);

    auto profileVert = cgGLGetLatestProfile(CG_GL_VERTEX);
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    cgGLSetOptimalOptions(profileVert);
    cgGLSetOptimalOptions(profileFrag);
    CgLog::Log("selecting vertex profile", _context);

    _knightDrawCall = new KnightDrawCall(_context, profileVert, profileFrag, _animVertShaderName, _vertEntry, _animFragShaderName, _fragEntry);
    _knightDrawCall->SetProjection(40, (float)width / (float)height, 0.1, 100);

}

KeyFrameAnim::~KeyFrameAnim()
{
    delete _knightDrawCall;
    delete _myKnightModel;
}