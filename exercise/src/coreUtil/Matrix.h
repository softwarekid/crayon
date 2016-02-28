/*
author : WangYi(Joe Wang)
created : 2015/10/30

purpose: a matrix computation class for square matrix

currently only support 4 * 4 matrix
*/

#ifndef Matrix_h__
#define Matrix_h__
#include "Vector4f.h"
class Matrix4f
{
public:
    int static const DIM;
    explicit Matrix4f();
    Matrix4f(const Matrix4f& m);
    //Matrix4f(const Matrix4f&& m);
    void SetZero();
    Matrix4f Mul(const Matrix4f& m);
    Vector4f Mul(const Vector4f& v);
    void SetIdentity();
    Matrix4f Invert();
    void GetInnerValue(float * innerValue) const;
    void Print();
    Matrix4f& operator = (const Matrix4f& m);
    //Matrix4f& operator = (const Matrix4f&& m);
    float& operator() (int rowIndex, int colIndex);
    ~Matrix4f();
private:
    inline void _SwapRow(double* a, double*b);
    float operator() (int row, int col) const;
    float *_pInnerValues;
};

#endif // Matrix_h__