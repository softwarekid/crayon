#include "Matrix.h"
#include <assert.h>
#include <string.h>
#include <cmath>
#include <iostream>
using namespace std;

int const Matrix4f::DIM = 4;

Matrix4f::Matrix4f()
{
    _pInnerValues = new float[DIM* DIM];
    SetZero();
}

Matrix4f::Matrix4f(const Matrix4f& m)
{
    _pInnerValues = new float[DIM * DIM];
    for (int i = 0; i < DIM * DIM; i++)
    {
        _pInnerValues[i] = m._pInnerValues[i];
    }
}

Matrix4f& Matrix4f::operator = (const Matrix4f& m)
{
    for (int i = 0; i < DIM * DIM; i++)
    {
        _pInnerValues[i] = m._pInnerValues[i];
    }
    return *this;
}

void Matrix4f::SetZero()
{
    memset(_pInnerValues, 0, sizeof(float) * DIM * DIM);
}

void Matrix4f::SetIdentity()
{
    SetZero();
    for (int i = 0; i < DIM * DIM ; i += (DIM + 1))
    {
        _pInnerValues[i] = 1;
    }
}

Matrix4f Matrix4f::Mul(const Matrix4f& m)
{
    Matrix4f result;
    for (int i = 1; i <= DIM ; i++)
    {
        for (int j = 1; j <= DIM; j++)
        {
            for (int k = 1; k <= DIM; k++)
            {
                result(i, j) += operator()(i, k) * m(k, j);
            }
        }
    }
    return result;
}

Vector4f Matrix4f::Mul(const Vector4f& v)
{
    Vector4f result;
    Matrix4f m(*this);
    for (int i = 1; i <= DIM; i++)
    {
        for(int j = 1; j <= DIM; j++)
        {
            result[i] += v[j] * m(i,j);
        }
    }
    return result;
}

void Matrix4f::_SwapRow(double* a, double* b)
{
    double* temp = a;
    a = b;
    b = temp;
}

Matrix4f Matrix4f::Invert()
{
    /* Assumes matrices are ROW major. */
    double wtmp[4][8];
    double m0, m1, m2, m3, s;
    double *r0, *r1, *r2, *r3;

    r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];
    float a = this->operator() (1,1);


    r0[0] = this->operator() (1,1), r0[1] = this->operator() (1,2),
    r0[2] = this->operator() (1,3), r0[3] = this->operator() (1,4),
    r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,

    r1[0] = this->operator() (2,1), r1[1] = this->operator() (2,2),
    r1[2] = operator() (2,3), r1[3] = operator() (2,4),
    r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,

    r2[0] = operator() (3,1), r2[1] = operator() (3,2),
    r2[2] = operator() (3,3), r2[3] = operator() (3,4),
    r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,

    r3[0] = operator() (4,1), r3[1] = operator() (4,2),
    r3[2] = operator() (4,3), r3[3] = operator() (4,4),
    r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;

    /* Choose myPivot, or die. */
    if (fabs(r3[0])>fabs(r2[0])) _SwapRow(r3, r2);
    if (fabs(r2[0])>fabs(r1[0])) _SwapRow(r2, r1);
    if (fabs(r1[0])>fabs(r0[0])) _SwapRow(r1, r0);
    if (0.0 == r0[0]) 
    {
        assert(!"could not invert matrix");
    }

    /* Eliminate first variable. */
    m1 = r1[0]/r0[0]; m2 = r2[0]/r0[0]; m3 = r3[0]/r0[0];
    s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
    s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
    s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
    s = r0[4];
    if (s != 0.0) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
    s = r0[5];
    if (s != 0.0) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
    s = r0[6];
    if (s != 0.0) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
    s = r0[7];
    if (s != 0.0) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

    /* Choose myPivot, or die. */
    if (fabs(r3[1])>fabs(r2[1])) _SwapRow(r3, r2);
    if (fabs(r2[1])>fabs(r1[1])) _SwapRow(r2, r1);
    if (0.0 == r1[1]) 
    {
        assert(!"could not invert matrix");
    }

    /* Eliminate second variable. */
    m2 = r2[1]/r1[1]; m3 = r3[1]/r1[1];
    r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
    r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
    s = r1[4]; if (0.0 != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
    s = r1[5]; if (0.0 != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
    s = r1[6]; if (0.0 != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
    s = r1[7]; if (0.0 != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

    /* Choose myPivot, or die. */
    if (fabs(r3[2])>fabs(r2[2])) _SwapRow(r3, r2);
    if (0.0 == r2[2]) {
        assert(!"could not invert matrix");
    }

    /* Eliminate third variable. */
    m3 = r3[2]/r2[2];
    r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
        r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
        r3[7] -= m3 * r2[7];

    /* Last check. */
    if (0.0 == r3[3]) {
        assert(!"could not invert matrix");
    }

    s = 1.0/r3[3];              /* Now back substitute row 3. */
    r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

    m2 = r2[3];                 /* Now back substitute row 2. */
    s  = 1.0/r2[2];
    r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
        r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
    m1 = r1[3];
    r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
        r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
    m0 = r0[3];
    r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
        r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

    m1 = r1[2];                 /* Now back substitute row 1. */
    s  = 1.0/r1[1];
    r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
        r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
    m0 = r0[2];
    r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
        r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

    m0 = r0[1];                 /* Now back substitute row 0. */
    s  = 1.0/r0[0];
    r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
        r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);


    Matrix4f result;
    result(1,1) = r0[4]; result(1,2) = r0[5], result(1,3) = r0[6]; result(1,4) = r0[7],
    result(2,1) = r1[4]; result(2,2) = r1[5], result(2,3) = r1[6]; result(2,4) = r1[7],
    result(3,1) = r2[4]; result(3,2) = r2[5], result(3,3) = r2[6]; result(3,4) = r2[7],
    result(4,1) = r3[4]; result(4,2) = r3[5], result(4,3) = r3[6]; result(4,4) = r3[7]; 
    return result;
}

void Matrix4f::GetInnerValue(float* innerValue)
{
    for(int i = 0; i < DIM * DIM; i++)
    {
        innerValue[i] = _pInnerValues[i];
    }
}

// row and col index starts from 1
float& Matrix4f::operator() (int row, int col) 
{
    assert(row > 0 && row <= DIM);
    assert(col > 0 && col <= DIM);
    return _pInnerValues[(row - 1) * DIM + (col - 1)];
}

float Matrix4f::operator()(int row, int col) const
{
    assert(row > 0 && row <= DIM);
    assert(col > 0 && col <= DIM);
    return _pInnerValues[(row - 1) * DIM + (col - 1)];
}

Matrix4f::~Matrix4f()
{
    delete[] _pInnerValues;
}

void Matrix4f::Print()
{
    for (int i = 1; i <= DIM; i++)
    {
        for (int j = 1; j <= DIM; j++)
        {
            cout<< this->operator()(i, j) << "      ";
        }
        cout<<endl;
    }
}
