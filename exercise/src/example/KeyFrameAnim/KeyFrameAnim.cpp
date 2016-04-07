#include "KeyFrameAnim.h"
#include <CG/cgGL.h>
#include <CgLog.h>
#include <iostream>
#include <GL/glut.h>

float KeyFrameAnim::_AddDeltaFrame(float baseFrameKnob, float delta)
{
    auto frameKnob= delta + baseFrameKnob;
    while (frameKnob >= _myKnightModel->header.numFrames)
    {
        frameKnob -= _myKnightModel->header.numFrames;
    }
    if (frameKnob < 0) 
    {
        frameKnob = 0;  /* Just to be sure myFrameKnob is never negative. */
    }
    return frameKnob;
}

void KeyFrameAnim::_Idle()
{
    static int myLastElapsedTime;
    const float millisecondsPerSecond = 1000.0f;
    const float keyFramesPerSecond = 3.0f;
    int now = glutGet(GLUT_ELAPSED_TIME);
    float delta = (now - myLastElapsedTime) / millisecondsPerSecond;
    myLastElapsedTime = now;  /* This time become "prior time". */

    delta *= keyFramesPerSecond;
    _myFrameKnob = _AddDeltaFrame(_myFrameKnob, delta);
    glutPostRedisplay();
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

    Camera camera(eyePosition, eyeCenter, eyeUp);
    Vector4f rotation(0,1,0,0);
    Vector3f translation(0,0,0);
    const int frameA = floor(_myFrameKnob);
    const int frameB = _AddDeltaFrame(_myFrameKnob, 1);
    _knightDrawCall->SetVaringParams(camera, rotation, translation, eyePosition, lightPosition,_myFrameKnob - floor(_myFrameKnob));
    _knightDrawCall->Draw([&](){drawMD2render(_myMD2render, frameA, frameB); });
    glutSwapBuffers();
}

void KeyFrameAnim::_LoadModelAndTexture()
{
    const string _modelPath = R"(src\example\KeyFrameAnim\knight.md2)";
    const string _texturePath = R"(src\example\KeyFrameAnim\knight.tga)";
    _myKnightModel = md2ReadModel(_modelPath.c_str());
    if (0 == _myKnightModel) 
    {
        cout << "load model failure\n";
        exit(1);
    }
    _myMD2render = createMD2render(_myKnightModel);
    gliGenericImage *decalImage;
    decalImage = readImage(_texturePath.c_str());
    glGenTextures(1, &name);
    glBindTexture(GL_TEXTURE_2D, name);
    decalImage = loadTextureDecal(decalImage, 1);
    gliFree(decalImage);
}

KeyFrameAnim::KeyFrameAnim(const char* title, int width, int height) : GlutWrapper(title, width, height)
{
    _LoadModelAndTexture();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    _context = cgCreateContext();
    CgLog::Log("create content", _context);
    cgGLSetDebugMode(CG_TRUE);
    cgSetParameterSettingMode(_context, CG_DEFERRED_PARAMETER_SETTING);

    auto profileVert = cgGLGetLatestProfile(CG_GL_VERTEX);
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    cgGLSetOptimalOptions(profileVert);
    cgGLSetOptimalOptions(profileFrag);
    CgLog::Log("selecting vertex profile", _context);

    _knightDrawCall = new KnightDrawCall(_context, profileVert, profileFrag, _animVertShaderName, _vertEntry, _animFragShaderName, _fragEntry);
    _knightDrawCall->SetProjection(40, (float)width / (float)height, 0.1, 100);

    const Vector3f lightColor(1,1,1);
    _knightDrawCall->SetConstParams(lightColor, name, 1.0f / _myKnightModel->header.skinWidth, 1.0f / _myKnightModel->header.skinHeight);
}

KeyFrameAnim::~KeyFrameAnim()
{
    delete _knightDrawCall;
    delete _myKnightModel;
}