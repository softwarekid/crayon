#include "TwoTextureAccess.h"
#include <CgLog.h>
#include <CG/cgGL.h>
#include "TwoTextureAccessFsParam.h"
#include "TwoTextureAccessVsParam.h"
#include <GL/glut.h>

void TwoTextureAccess::_Idle()
{
    if (seperation > 0.4)
    {
        seperationVelocity = -0.005;
    }
    else if (seperation< -0.4) 
    {
        seperationVelocity = 0.005;
    }
    seperation += seperationVelocity;
    glutPostRedisplay();
}

void TwoTextureAccess::_Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _InitShaderParams();
    _fragShader->BindProgram();
    _fragShader->EnableProfile();
    _vertShader->BindProgram();
    _vertShader->EnableProfile();
    if (seperation > 0) 
    {
        /* Separate in the horizontal direction. */
        _vertParams->SetLeftSeperation(-seperation, 0);
        _vertParams->SetRightSeperation(seperation, 0);
    }
    else 
    {
        /* Separate in the vertical direction. */
        _vertParams->SetLeftSeperation(0, -seperation);
        _vertParams->SetRightSeperation(0, seperation);
    }

    glBegin(GL_TRIANGLES);
    glTexCoord2f(0, 0);
    glVertex2f(-0.8, 0.8);

    glTexCoord2f(1, 0);
    glVertex2f(0.8, 0.8);

    glTexCoord2f(0.5, 1);
    glVertex2f(0.0, -0.8);
    glEnd();

    _vertShader->DisableProfile();
    _fragShader->DisableProfile();
    glutSwapBuffers();
}

void TwoTextureAccess::_InitShaderParams()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); /* Tightly packed texture data. */
    GLuint name;
    glGenTextures(1, &name);
    glBindTexture(GL_TEXTURE_2D, name);
    /* Load demon decal texture with mipmaps. */
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8,
        128, 128, GL_RGB, GL_UNSIGNED_BYTE, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR);
    _fragParams->SetTexture(name);
}

void TwoTextureAccess::_InitVertShader()
{
    auto profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
    string fileName(R"(src\example\TwoTextureAccess\TwoTextureAccess_V.cg)");
    string entry("main_v");
    _vertShader = new CgShader(_context, profileVertex, fileName, entry);
    _vertParams = new TwoTextureAccessVsParam(*_vertShader);
    _vertParams->ExtractParams();
    cgGLSetOptimalOptions(profileVertex);
}

void TwoTextureAccess::_InitFragShader()
{
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    string fileName(R"(src\example\TwoTextureAccess\TwoTextureAccess_F.cg)");
    string entry("main_f");
    _fragShader = new CgShader(_context, profileFrag, fileName, entry);
    _fragParams = new TwoTextureAccessFsParam(*_fragShader);
    _fragParams->ExtractParams();
    cgGLSetOptimalOptions(profileFrag);
}

TwoTextureAccess::TwoTextureAccess(const char* title, int width, int height, const GLubyte* texture) : GlutWrapper(title, width, height), _texture(texture)
{
    glEnable(GL_DEPTH_TEST);
    _context = cgCreateContext();
    CgLog::Log("create content", _context);
    cgGLSetDebugMode(CG_TRUE);
    cgSetParameterSettingMode(_context,CG_DEFERRED_PARAMETER_SETTING);
    CgLog::Log("selecting vertex profile", _context);
}