//#include <iostream>
//#include <stdlib.h>
//#include <cmath>
//#include <cassert>
//
//#include <GL/glew.h>
//#include <GL/glut.h>
//#include <GL/wglew.h>
//#include <Cg/cg.h>
//#include <CG/cgGL.h>
//#include "TransformUtility.h"
//using namespace std;
//
//
//// this part is unstable, you'd better extract it into a class
//#pragma region cg_parameters_definition
//static CGcontext context;
//static CGprofile profileVertex;
//static CGprofile profileFrament;
//static CGprogram programVertex;
//static CGprogram programFragment;
//
//static CGparameter paramVertexModelViewProj;
//static CGparameter paramVertexGolbalAmbient;
//static CGparameter paramVertexLightColor;
//static CGparameter paramVertexLightPosition;
//static CGparameter paramVertexEyePosition;
//static CGparameter paramVertexKe;
//static CGparameter paramVertexKa;
//static CGparameter paramVetexKd;
//
//static CGparameter paramFragmentLightColor;
//static CGparameter paramFragmentKs;
//static CGparameter paramFragmentShininess;
//#pragma endregion cg_parameters_definition
//
//
//static const char* programName = "vertFragMix";
//static const char* vertexProgramFileName = "vert.cg";
//static const char* vertexProgramEntry = "main_v";
//static const char* fragProgramFileName = "frag.cg";
//static const char* fragProgramEntry = "main_f";
//
//static float lightAngle = -0.4;   /* Angle light rotates around scene. */
//static float projectionMatrix[16];
//static float globalAmbient[3] = {0.1f, 0.1f, 0.1f};
//static float lightColor[3] = {0.95f, 0.95f, 0.95f};
//
//
//static void checkForCgError(string situation)
//{
//    CGerror error;
//    const char *string = cgGetLastErrorString(&error);
//
//    if (error != CG_NO_ERROR)
//    {
//        cout<< programName << situation.c_str()<< string;
//
//        if (error == CG_COMPILER_ERROR)
//        {
//            cout<< cgGetLastListing(context); 
//        }
//        exit(1);
//    }
//}
//
//* Forward declared GLUT callbacks registered by main. */
//static void reshape(int width, int height);
//static void display(void);
//static void keyboard(unsigned char c, int x, int y);
//static void menu(int item);
//static void requestSynchronizedSwapBuffers(void);
//
//void GetProgramParam(CGprogram program, CGparameter param, const char* name)
//{
//    param = cgGetNamedParameter(program, name);
//    string error("could not get param");
//    error += name;
//    checkForCgError(error);
//}
//
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
//        fprintf(stderr, "%s: failed to initialize GLEW, OpenGL 1.1 required.\n", myProgramName);
//        exit(1);
//    }
//
//    requestSynchronizedSwapBuffers();
//    glClearColor(0.1,0.1,0.1,0);
//    glEnable(GL_DEPTH_TEST);
//
//    context = cgCreateContext();
//    checkForCgError("create content");
//    cgGLSetDebugMode(CG_FALSE);
//    cgSetParameterSettingMode(context,CG_DEFERRED_PARAMETER_SETTING);
//
//    profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
//    cgGLSetOptimalOptions(profileVertex);
//    checkForCgError("selecting vertex profile");
//
//    programVertex = cgCreateProgramFromFile(
//        context,
//        CG_SOURCE,
//        vertexProgramFileName,
//        profileVertex,
//        vertexProgramEntry,
//        NULL
//        );
//    checkForCgError("creating vertex program from file");
//    cgGLLoadProgram(programVertex);
//    checkForCgError("loading vertex program");
//
//    GetProgramParam(programVertex, paramVertexModelViewProj, "modelViewProj");
//    GetProgramParam(programVertex, paramVertexGolbalAmbient, "globalAmbient");
//    GetProgramParam(programVertex, paramVertexLightColor, "lightColor");
//    GetProgramParam(programVertex, paramVertexLightPosition, "lightPosition");
//    GetProgramParam(programVertex, paramVertexEyePosition, "eyePosition");
//    GetProgramParam(programVertex, paramVertexKe, "Ke");
//    GetProgramParam(programVertex, paramVertexKa, "Ka");
//    GetProgramParam(programVertex, paramVetexKd, "Kd");
//    GetProgramParam(programFragment, paramVertexEyePosition, "eyePosition");
//
//    cgSetParameter3fv(paramVertexGolbalAmbient, globalAmbient);
//    cgSetParameter3fv(paramVertexLightColor, lightColor);
//
//    profileFrament = cgGLGetLatestProfile(CG_GL_FRAGMENT);
//    cgGLSetOptimalOptions(profileFrament);
//    checkForCgError("selecting fragment profile");
//
//    programFragment = cgCreateProgramFromFile(
//        context,
//        CG_SOURCE,
//        fragProgramFileName,
//        profileFrament,
//        fragProgramEntry,
//        NULL);
//    checkForCgError("creating fragment program from string");
//    cgGLLoadProgram(programFragment);
//    checkForCgError("loading fragment program");
//
// /*   GetProgramParam(programFragment, paramFragmentKs, "Ks");
//    GetProgramParam(programFragment, paramFragmentShininess, "shininess");
//    GetProgramParam(programFragment, paramFragmentLightColor, "lightColor");*/
//    glutCreateMenu(menu);
//    glutAddMenuEntry("[ ] Animate", ' ');
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//    glutMainLoop();
//    return 0;
//}
//
//
//static void reshape(int width, int height)
//{
//    float aspectRatio = (float)width / (float) height;
//    float fov = 40.0f;
//    TransformUtility.BuildPerspectiveMatrix(fov,aspectRatio,
//                                            1.0, 20.0,//Znear and Zfar
//                                            projectionMatrix);
//    glViewport(0, 0, width, height);
//}
//
//static void display()
//{
//    const float eyePosition[4] = {0, 0, 13, 1};
//    const float lightPosition[4] = {5 * sin(lightAngle),
//                                    1.5,
//                                    5 * cos(lightAngle),1};
//
//    
//}