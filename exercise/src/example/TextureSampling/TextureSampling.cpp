#include "TextureSampling.h"
#include <GL/glut.h>

void TextureSampling::_Reshape(int width, int height)
{
    float aspectRatio = (float)width / (float) height;
    float fov = 40.0f;
    _transform.SetProjection(fov,aspectRatio,1.0, 20.0);
    glViewport(0, 0, width, height);
}

void TextureSampling::_Display()
{
}

void TextureSampling::_InitShaderParams()
{
}
