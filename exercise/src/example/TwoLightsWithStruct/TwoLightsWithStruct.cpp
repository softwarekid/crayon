#include "TwoLightsWithStruct.h"
#include <CG/cgGL.h>
using namespace std;
void TwoLightsWithStruct::_InitVertShader()
{
    auto profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
    string fileName(R"(src\example\TextureSampling\TextureSampling_V.cg)");
    string entry("main_v");
    _vertShader = new CgShader(_context, profileVertex, fileName, entry);
    _vertParams = new TwoLightsWithStructVsParam(*_vertShader);
    _vertParams->ExtractParams();
    cgGLSetOptimalOptions(profileVertex);
}

TwoLightsWithStruct::TwoLightsWithStruct(const char* title, int width, int height) : GlutWrapper(title, width, height)
{

}