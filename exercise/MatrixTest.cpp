#include "MatrixTest.h"
#include "cppunit/TestAssert.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MatrixTest);
void MatrixTest::setUp()
{
}

void MatrixTest::tearDown()
{
}

void MatrixTest::testAssignOperator()
{
    Matrix4f m1;
    Matrix4f m2;
    m2(1,1) = 1;
    m1 = m2;
    _MatrixEqualHelper(m1, m2);
    CPPUNIT_ASSERT_EQUAL(1.0f, m1(1,1));
}

void MatrixTest::testSetIdentity()
{
    Matrix4f m1;
    m1.SetIdentity();
    int dim = Matrix4f::DIM;
    for (int i = 1; i <= dim; i++)
    {
        for (int j = 1; j <= dim; j++)
        {
            if (i == j)
            {
                CPPUNIT_ASSERT_EQUAL(1.0f, m1(i, j));
            }
        }
    }
}

void MatrixTest::testInvert()
{
    Matrix4f m1;
    Matrix4f m2;
    m2.SetIdentity();
    m2(1, 1) = 2; m2(1, 2) = 1;
                  m2(2, 2) = 2; 
                                m2(3, 3) = 2;
                                              m2(4, 4) = 1;
    m1 = m2.Invert();

    CPPUNIT_ASSERT_EQUAL(m1(1,1), 0.5f);
    CPPUNIT_ASSERT_EQUAL(m1(1,2), -0.25f);
    CPPUNIT_ASSERT_EQUAL(m1(2,2), 0.5f);
    CPPUNIT_ASSERT_EQUAL(m1(3,3), 0.5f);
    CPPUNIT_ASSERT_EQUAL(m1(4,4), 1.0f);
}

void MatrixTest::testMul()
{
    Matrix4f m1;
    Matrix4f m2;
    Matrix4f m3;
    m1.SetIdentity();
    m2(1, 1) = 2;
    m2(3, 4) = 4;
    m3 = m2.Mul(m1);
    _MatrixEqualHelper(m2, m3);

    
}

void MatrixTest::_MatrixEqualHelper(Matrix4f& m1, Matrix4f& m2)
{
    int dim = Matrix4f::DIM;
    for (int i = 1; i <= dim; i++)
    {
        for (int j = 1; j <= dim; j++)
        {
            CPPUNIT_ASSERT_EQUAL(m1(i,j), m2(i,j));
        }
    }
}
