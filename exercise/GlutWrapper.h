#ifndef glut_wrapper_h
#define glut_wrapper_h
#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"
#include "VertShader.h"
#include "FragmentShader.h"
#include <map>

class GlutWrapper
{
private:
    // only static member function can be used as callback, because it 
    // doesn't have the implicit "this" parameter
    static void __Keyboard(unsigned char c , int x, int y);
    static void __Idle(void);
    static void __Reshape(int width, int height);
    static void __Display(void);
    static void __Menu();
    static GlutWrapper* __CurrentWindow();
    static std::map<int, GlutWrapper*> _windows;

protected:
    virtual void _Draw() = 0;
    virtual void _Keyboard(int c, int x, int y);
    virtual void _Idle(void);
    virtual void _Reshape(int width, int height);
    virtual void _Display(void);
    virtual void _Menu();


    virtual void Init();
private:
    void _RequestSynchronizedSwapBuffers();

    int _windowID;
    float _lightAngle;
    int _width;
    int _height;
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
    virtual ~GlutWrapper();
};
#endif