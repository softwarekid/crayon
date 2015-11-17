#include "VectorTest.h"
#include "cppunit/TestAssert.h"
#include <cmath>
#include "Constants.h"

CPPUNIT_TEST_SUITE_REGISTRATION(VectorTest);
void VectorTest::setUp()
{

}

void VectorTest::tearDown()
{

}

void VectorTest::TestConstructor()
{
    Vector4f v1;
    Vector4f v2(1, 2, 3, 4);

    CPPUNIT_ASSERT_EQUAL(0.0f, v1[0]);
    CPPUNIT_ASSERT_EQUAL(1.0f, v2[0]);
    CPPUNIT_ASSERT_EQUAL(2.0f, v2[1]);

    Vector3f v3(1,2,4);
    CPPUNIT_ASSERT_EQUAL(1.0f, v3[0]);
    CPPUNIT_ASSERT_EQUAL(2.0f, v3[1]);
}

void VectorTest::TestAssign()
{
    Vector4f v1;
    Vector4f v2(1, 2, 3, 4);
    v1 = v2;
    CPPUNIT_ASSERT(_IsVectorEqual(v1, v2));

    Vector3f v3;
    Vector3f v4(1, 2, 3);
    v3 = v4;
}

bool VectorTest::_IsVectorEqual(const Vector4f& v1, const Vector4f& v2)
{
    for (int i = 0; i < Vector4f::DIM; i++)
    {
        if (fabs(v1[i] - v2[i]) > Constants::Math::EPSILON) 
            return false;
    }
    return true;
}

bool VectorTest::_IsVectorEqual(const Vector3f& v1, const Vector3f& v2)
{
    for (int i = 0; i < Vector3f::DIM; i++)
    {
        if (fabs(v1[i] - v2[i]) > Constants::Math::EPSILON) 
            return false;
    }
    return true;
}

void VectorTest::TestMinus()
{
    Vector3f v1(1,2,3);
    Vector3f v2(5,6,7);
    
    v1 = v2 - v1;
    Vector3f result(4,4,4);
    CPPUNIT_ASSERT(_IsVectorEqual(v1, result));

    Vector4f v3(1, 2, 3, 1);
    Vector4f v4(5, 6, 7, 1);
    v3 = v4 - v3;
    Vector4f result1(4, 4, 4, 0);
    CPPUNIT_ASSERT(_IsVectorEqual(result1, v3));
}

void VectorTest::TestMul()
{
    Vector3f v1(1,2,3);
    v1 = v1 * 2;
    
    Vector3f result(2,4,6);
    CPPUNIT_ASSERT(_IsVectorEqual(v1, result));
}

void VectorTest::TestCross()
{
    Vector3f v1(1,2,3);
    Vector3f v2(2,4,5);
    v1 = v1.Cross(v2);
    
    Vector3f result(-2, 1, 0);
    CPPUNIT_ASSERT(_IsVectorEqual(v1, result));
}

void VectorTest::TestDot()
{
    Vector3f v1(1,2,3);
    Vector3f v2(2,4,5);
    float result = v1.Dot(v2);
    CPPUNIT_ASSERT(result, 25.0f);
}

void VectorTest::TestGetter()
{
    Vector3f v(1,2,3);
    CPPUNIT_ASSERT_EQUAL(v[0], 1.0f);
    CPPUNIT_ASSERT_EQUAL(v[1], 2.0f);
    CPPUNIT_ASSERT_EQUAL(v[2], 3.0f);
}

void VectorTest::TestLength()
{
    Vector3f v1(1,2,2);
    float length = v1.Length();
    CPPUNIT_ASSERT_EQUAL(3.0f,length);
    
    Vector3f v2;
    length = v2.Length();
    CPPUNIT_ASSERT_EQUAL(0.0f, length);
}

void VectorTest::TestNormalized()
{
    Vector3f v(1,2,4);
    v.Normalized();
    float length = v.Length();
    CPPUNIT_ASSERT(fabs(1.0f - length) < Constants::Math::EPSILON);
}
