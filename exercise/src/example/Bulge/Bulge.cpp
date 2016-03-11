#include "Bulge.h"
#include <CG/cgGL.h>
#include "BulgeVsParam.h"
#include "BulgeFsParam.h"
#include <CgLog.h>

void Bulge::_Display()
{
    
}

void Bulge::_InitVertShader()
{
    auto profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
    std::string fileName(R"(src\example\Bulge\bulge_V.cg)");
    std::string entry("main_v");
    _vertShader = new CgShader(_context, profileVertex, fileName, entry);
    _vertParams = new BulgeVsParam(*_vertShader);
    _vertParams->ExtractParams();
    cgGLSetOptimalOptions(profileVertex);
}

void Bulge::_InitFragShader()
{
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    std::string fileName(R"(src\example\Bulge\bulge_F.cg)");
    std::string entry("main_f");
    _fragShader = new CgShader(_context, profileFrag, fileName, entry);
    _fragParams = new BulgeFsParam(*_fragShader);
    _fragParams->ExtractParams();
    cgGLSetOptimalOptions(profileFrag);
}

Bulge::Bulge(const char* title, int width, int height) : GlutWrapper(title, width, height)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1, 0.1, 0.1, 0);  /* Gray background. */
    _context = cgCreateContext();
    CgLog::Log("create content", _context);
    cgGLSetDebugMode(CG_TRUE);
    cgSetParameterSettingMode(_context,CG_DEFERRED_PARAMETER_SETTING);
    CgLog::Log("selecting vertex profile", _context);
}