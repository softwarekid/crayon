#include "Mesh.h"
#include <GL/glut.h>
void Mesh::Render()
{
    glutSolidSphere(2.0, 10, 10);
}