#include "TextureSampling.h"
#include "TextureSamplingVsParam.h"
#include "TextureSamplingFsParam.h"
#include <CG/cgGL.h>
#include <CgLog.h>
#include <GL/glut.h>
using namespace std;
void TextureSampling::_Reshape(int width, int height)
{
    float aspectRatio = (float)width / (float) height;
    float fov = 40.0f;
    _transform.SetProjection(fov,aspectRatio,1.0, 20.0);
    glViewport(0, 0, width, height);
}

void TextureSampling::_Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _InitShaderParams();
    _vertShader->BindProgram();
    _vertShader->EnableProfile();
    _fragShader->BindProgram();
    _fragShader->EnableProfile();
    _fragParams->EnableTexture();

    glBegin(GL_TRIANGLES);
    glTexCoord2f(0, 0);
    glVertex2f(-0.8, 0.8);

    glTexCoord2f(1, 0);
    glVertex2f(0.8, 0.8);

    glTexCoord2f(0.5, 1);
    glVertex2f(0.0, -0.8);
    glEnd();

    _fragParams->DisableTexture();
    _vertShader->DisableProfile();
    _fragShader->DisableProfile();
    glutSwapBuffers();
}

void TextureSampling::_InitShaderParams()
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

void TextureSampling::_InitVertShader()
{
    auto profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
    string fileName(R"(src\example\TextureSampling\TextureSampling_V.cg)");
    string entry("main_v");
    _vertShader = new CgShader(_context, profileVertex, fileName, entry);
    _vertParams = new TextureSamplingVsParam(*_vertShader);
    _vertParams->ExtractParams();
    cgGLSetOptimalOptions(profileVertex);
}

void TextureSampling::_InitFragShader()
{
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    string fileName(R"(src\example\TextureSampling\TextureSampling_F.cg)");
    string entry("main_f");
    _fragShader = new CgShader(_context, profileFrag, fileName, entry);
    _fragParams = new TextureSamplingFsParam(*_fragShader);
    _fragParams->ExtractParams();
    cgGLSetOptimalOptions(profileFrag);
}

TextureSampling::TextureSampling(const char* title, int width, int height, const GLubyte* texture) : GlutWrapper(title, width, height), _texture(texture)
{
    glEnable(GL_DEPTH_TEST);
    _context = cgCreateContext();
    CgLog::Log("create content", _context);
    cgGLSetDebugMode(CG_TRUE);
    cgSetParameterSettingMode(_context,CG_DEFERRED_PARAMETER_SETTING);
    CgLog::Log("selecting vertex profile", _context);
}