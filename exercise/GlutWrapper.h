#ifndef glut_wrapper_h
#define glut_wrapper_h
#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"
#include <map>
#include <Cg/cg.h>
#include "CgShader.h"

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
    virtual void _Keyboard(int c, int x, int y);
    virtual void _Idle(void);
    virtual void _Reshape(int width, int height);
    virtual void _Display(void) = 0;
    virtual void _Menu();
    virtual void _Exit();
    virtual void InitVertShader() = 0;
    virtual void InitFragShader() = 0;

    Transform _transform;
    CgShader* _vertShader;
    CgShader* _fragShader;
private:
    void _RequestSynchronizedSwapBuffers();

    int _windowID;
    int _width;
    int _height;

    CGcontext _context;
    Mesh _mesh;
public:
    void SetTranslate(float x, float y, float z);
    void SetRotation(float angle, float axis_x, float axis_y, float axis_z);
    void SetCamera(Camera camera);
    void SetMesh(Mesh mesh);
    inline void SetRenderingFixture(CGcontext context, const CgShader& vertShader, const CgShader& fragShader);
    GlutWrapper(const char* title, int width, int height);
    virtual ~GlutWrapper();
};
#endif