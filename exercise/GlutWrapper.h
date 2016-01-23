#ifndef glut_wrapper_h
#define glut_wrapper_h
#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"
#include "VertShader.h"
#include "FragmentShader.h"

class GlutWrapper
{
private:
    // only static member function can be used as callback, because it 
    // doesn't have the implicit "this" parameter
    static void keyboard(unsigned char c , int x, int y);
    static void _idle(void);
    static void _reshape(int width, int height);
    static void _display(void);
    static void _menu();

    void requestSynchronizedSwapBuffers();

    float _lightAngle;
    int _width;
    int _height;

private:
    Transform transform;
    VerShader verShader;
    FragmentShader fragmentShader;
    Mesh mesh;
public:
    void SetTransform(float x, float y, float z);
    void SetRotation(float angle, float axis_x, float axis_y, float axis_z);
    void SetCamera(Camera camera);
    void SetMesh(Mesh mesh);
    void UpdateParam();
    GlutWrapper(const char* title, int width, int height, float lightAngle);
};
#endif
