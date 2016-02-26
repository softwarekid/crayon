#include "example/TextureSampling/TextureSampling.h"

static const GLubyte
myDemonTextureImage[3 * (128 * 128)] = {
    /* RGB8 image data for a mipmapped 128x128 demon texture */
#include "demon_image.h"
};

int main()
{
    TextureSampling cgViewer("crayon", 400, 400, myDemonTextureImage);
    cgViewer.StartRendering();
    return 0;
}