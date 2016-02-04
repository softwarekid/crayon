#include "CgViewer.h"

int main()
{
    CgViewer cgViewer("crayon", 400, 400, -0.4f);
    cgViewer.StartRendering();
    return 0;
}