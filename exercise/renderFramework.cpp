#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "Transform.h"
#include "Constants.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/wglew.h>
#include <Cg/cg.h>
#include <CG/cgGL.h>
using namespace std;


// this part is unstable, you'd better extract it into a class
#pragma region cg_parameters_definition
static CGcontext context;
static CGprofile profileVertex;
static CGprofile profileFragment;
static CGprogram programVertex;
static CGprogram programFragment;
//
static CGparameter paramVertexmodelViewProj;
//static CGparameter paramVertexGolbalAmbient;
//static CGparameter paramVertexLightColor;
static CGparameter paramVertexLightPosition;
static CGparameter paramVertexEyePosition;
//static CGparameter paramVertexKe;
//static CGparameter paramVertexKa;
//static CGparameter paramVertexKd;

static CGparameter paramFragmentModelViewProj;
static CGparameter paramFragmentGolbalAmbient;
static CGparameter paramFragmentLightColor;
static CGparameter paramFragmentLightPosition;
static CGparameter paramFragmentEyePosition;
static CGparameter paramFragmentKe;
static CGparameter paramFragmentKa;
static CGparameter paramFragmentKd;

static CGparameter paramFragmentKs;
static CGparameter paramFragmentShininess;
#pragma endregion cg_parameters_definition


static const char* programName = "vertFragMix";
static const char* vertexProgramFileName = "vert.cg";
static const char* vertexProgramEntry = "main_v";
static const char* fragProgramFileName = "frag.cg";
static const char* fragProgramEntry = "main_f";

static float lightAngle = -0.4;   /* Angle light rotates around scene. */
static float projectionMatrix[16];
static float globalAmbient[3] = {0.1f, 0.1f, 0.1f};
static float lightColor[3] = {0.95f, 0.95f, 0.95f};


Transform transform;
static void Log(string situation)
{
    CGerror error;
    const char *string = cgGetLastErrorString(&error);

    if (error != CG_NO_ERROR)
    {
        cout<< programName << "\n" << situation.c_str()<< " " << string<<endl;

        if (error == CG_COMPILER_ERROR)
        {
            cout<< cgGetLastListing(context)<<endl; 
        }
        exit(1);
    }
}

/* Forward declared GLUT callbacks registered by main. */
static void reshape(int width, int height);
static void display(void);
static void keyboard(unsigned char c, int x, int y);
static void menu(int item);
static void requestSynchronizedSwapBuffers(void);

static void GetProgramParam(CGprogram program, CGparameter& param, const char* name)
{
    param = cgGetNamedParameter(program, name);
    string error("could not get param");
    error += name;
    Log(error);
}

static void CgSetParam(CGparameter param, Vector4f value)
{
    float innerValue[4] = {0};
    value.GetInnerArray(innerValue);
    cgSetParameter3fv(param, innerValue);
}

void CgSetParam(CGparameter param, Matrix4f value)
{
    float innerValue[16];
    value.GetInnerValue(innerValue);
    cgSetMatrixParameterfr(param, innerValue);
}

static void idle(void)
{
    lightAngle += 0.008;
    if(lightAngle > 2 * Constants::Math::PI)
    {
        lightAngle -= 2 * Constants::Math::PI;
    }
    glutPostRedisplay();
}

static void keyboard(unsigned char c, int x, int y)
{
    static int animating = 0;

    switch (c)
    {
    case 'p':
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutPostRedisplay();
        break;
    case 'l':
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glutPostRedisplay();
        break;
    case ' ':
        animating = !animating; /* Toggle */
        if (animating)
        {
            glutIdleFunc(idle);
        }
        else 
        {
            glutIdleFunc(NULL);
        }    
        break;
    case 27:  /* Esc key */
        /* Demonstrate proper deallocation of Cg runtime data structures.
        Not strictly necessary if we are simply going to exit. */
        cgDestroyProgram(programVertex);
        cgDestroyContext(context);
        exit(0);
        break;
    }
}

static void menu(int item)
{
    /* Pass menu item character code to keyboard callback. */
    keyboard((unsigned char)item, 0, 0);
}

//int main(int argc, char **argv)
//{
//    glutInitWindowSize(400,400);
//    glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
//    glutInit(&argc, argv);
//
//    glutCreateWindow(programName);
//    glutDisplayFunc(display);
//    glutKeyboardFunc(keyboard);
//    glutReshapeFunc(reshape);
//
//    if (glewInit() != GLEW_OK || !GLEW_VERSION_1_1)
//    {
//        fprintf(stderr, "%s: failed to initialize GLEW, OpenGL 1.1 required.\n", programName);
//        exit(1);
//    }
//
//    requestSynchronizedSwapBuffers();
//    glClearColor(0.1, 0.3, 0.6, 0.0);  /* Blue background */
//    //glClearColor(0.1,0.1,0.1,0);
//    glEnable(GL_DEPTH_TEST);
//
//    context = cgCreateContext();
//    Log("create content");
//    cgGLSetDebugMode(CG_TRUE);
//    cgSetParameterSettingMode(context,CG_DEFERRED_PARAMETER_SETTING);
//
//    profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
//    cgGLSetOptimalOptions(profileVertex);
//    Log("selecting vertex profile");
//
//    programVertex = cgCreateProgramFromFile(
//        context,
//        CG_SOURCE,
//        vertexProgramFileName,
//        profileVertex,
//        vertexProgramEntry,
//        NULL
//        );
//    Log("creating vertex program from file");
//    cgGLLoadProgram(programVertex);
//    Log("loading vertex program");
//
//    GetProgramParam(programVertex, paramVertexmodelViewProj, "modelViewProj");
//    //GetProgramParam(programVertex, paramVertexGolbalAmbient, "globalAmbient");
//    //GetProgramParam(programVertex, paramVertexLightColor, "lightColor");
//    GetProgramParam(programVertex, paramVertexLightPosition, "lightPosition");
//    GetProgramParam(programVertex, paramVertexEyePosition, "eyePosition");
//    //GetProgramParam(programVertex, paramVertexKe, "Ke");
//    //GetProgramParam(programVertex, paramVertexKa, "Ka");
//    //GetProgramParam(programVertex, paramVertexKd, "Kd");
//
//    //cgSetParameter3fv(paramVertexGolbalAmbient, globalAmbient);
//    //Log("set vertex program global ambient ");
//    //cgSetParameter3fv(paramVertexLightColor, lightColor);
//
//    profileFragment = cgGLGetLatestProfile(CG_GL_FRAGMENT);
//    cgGLSetOptimalOptions(profileFragment);
//    Log("selecting fragment profile");
//
//    programFragment = cgCreateProgramFromFile(
//        context,
//        CG_SOURCE,
//        fragProgramFileName,
//        profileFragment,
//        fragProgramEntry,
//        NULL);
//    Log("creating fragment program from string");
//    cgGLLoadProgram(programFragment);
//    Log("loading fragment program");
//
//    GetProgramParam(programFragment, paramFragmentGolbalAmbient, "globalAmbient");
//    GetProgramParam(programFragment, paramFragmentLightColor, "lightColor");
//    GetProgramParam(programFragment, paramFragmentLightPosition, "lightPosition");
//    //GetProgramParam(programFragment, paramFragmentEyePosition, "eyePosition");
//    GetProgramParam(programFragment, paramFragmentKe, "Ke");
//    GetProgramParam(programFragment, paramFragmentKa, "Ka");
//    GetProgramParam(programFragment, paramFragmentKd, "Kd");
//    GetProgramParam(programFragment, paramFragmentKs, "Ks");
//    GetProgramParam(programFragment, paramFragmentShininess, "shininess");
//
//    CgSetParam(paramFragmentGolbalAmbient, globalAmbient);
//    Log("set vertex program global ambient ");
//    cgSetParameter3fv(paramFragmentLightColor, lightColor);
//    glutCreateMenu(menu);
//    glutAddMenuEntry("[ ] Animate", ' ');
//    glutAddMenuEntry("[ ] polygon", 'p');
//    glutAddMenuEntry("[ ] line", 'l');
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
//    glutMainLoop();
//    return 0;
//}
//

static void reshape(int width, int height)
{
    float aspectRatio = (float)width / (float) height;
    float fov = 40.0f;
    transform.SetProjection(fov,aspectRatio,1.0, 20.0);
    glViewport(0, 0, width, height);
}

static void setBrassMaterial(void)
{
    const float brassEmissive[3] = {0.0,  0.0,  0.0},
        brassAmbient[3]  = {0.33, 0.22, 0.03},
        brassDiffuse[3]  = {0.78, 0.57, 0.11},
        brassSpecular[3] = {0.99, 0.91, 0.81},
        brassShininess = 27.8;

    cgSetParameter3fv(paramFragmentKe, brassEmissive);
    cgSetParameter3fv(paramFragmentKa, brassAmbient);
    cgSetParameter3fv(paramFragmentKd, brassDiffuse);
    cgSetParameter3fv(paramFragmentKs, brassSpecular);
    cgSetParameter1f(paramFragmentShininess, brassShininess);
}

static void display()
{
    const Vector3f eyePosition(0, 0, 13);
    const Vector3f eyeCenter(0,0,0);
    const Vector3f eyeUp(0,1,0);
    const Vector3f lightPosition(5 * sin(lightAngle), 1.5, 5 * cos(lightAngle));
    Camera camera(eyePosition, eyeCenter, eyeUp);
    transform.SetCamera(camera);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cgGLBindProgram(programVertex);
    Log("binding vertex program");

    cgGLEnableProfile(profileVertex);
    Log("enabling vertex profile");

    cgGLBindProgram(programFragment);
    Log("binding fragment program");

    cgGLEnableProfile(profileFragment);
    Log("enabling fragment profile");

    setBrassMaterial();
    transform.SetTranslate(2, 0, 0);
    transform.SetArbitraryRotation(20, 1, 1, 1);
    Matrix4f modelMatrix;
    transform.GetModelMatrix(modelMatrix);
    Matrix4f invModelMatrix = modelMatrix.Invert();
    Vector4f objSpaceEyePosition = invModelMatrix.Mul(eyePosition);
    Vector4f objSpaceLightPosition = invModelMatrix.Mul(lightPosition);
    Matrix4f modelViewProjMatix;
    transform.GetMVPMatrix(modelViewProjMatix);
    CgSetParam(paramVertexmodelViewProj, modelViewProjMatix);

    //CgSetParam(paramFragmentEyePosition, objSpaceEyePosition);
    CgSetParam(paramFragmentLightPosition, objSpaceLightPosition);

    CgSetParam(paramVertexLightPosition, objSpaceLightPosition);
    CgSetParam(paramVertexEyePosition, objSpaceEyePosition);

    cgUpdateProgramParameters(programVertex);
    cgUpdateProgramParameters(programFragment);
    glutSolidSphere(2.0, 10, 10);

    cgGLDisableProfile(profileVertex);
    Log("disabling vertex profile");

    cgGLDisableProfile(profileFragment);
    Log("disabling fragment profile");
    glutSwapBuffers();
}

static void requestSynchronizedSwapBuffers(void)
{
#ifdef _WIN32
    if(wglSwapIntervalEXT)
    {
        wglSwapIntervalEXT(1);
    }
#endif
}