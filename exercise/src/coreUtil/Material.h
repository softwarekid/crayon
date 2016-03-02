#ifndef material_h__
#define material_h__
#include "Vector3f.h"
#include <initializer_list>

struct Material
{
public:
    Material(){};
    Vector3f ke;
    Vector3f ka;
    Vector3f kd;
    Vector3f ks;
    float shininess;
};

#endif