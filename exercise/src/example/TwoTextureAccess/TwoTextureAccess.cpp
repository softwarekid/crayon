#include "TwoTextureAccess.h"
#include <CgLog.h>
#include <CG/cgGL.h>
#include "TwoTextureAccessFsParam.h"
#include "TwoTextureAccessVsParam.h"

void TwoTextureAccess::_Display()
{

}

void TwoTextureAccess::_InitShaderParams()
{
    
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