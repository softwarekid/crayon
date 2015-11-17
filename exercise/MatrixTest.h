#ifndef MatrixTest_h__
#define MatrixTest_h__

#include <cppunit/extensions/HelperMacros.h>

#include "Matrix.h"
class MatrixTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(MatrixTest);
    CPPUNIT_TEST(testMul);
    CPPUNIT_TEST(testSetIdentity);
    CPPUNIT_TEST(testInvert);
    CPPUNIT_TEST(testAssignOperator);
    //CPPUNIT_TEST();
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void testMul();
    void testSetIdentity();
    void testInvert();
    void testAssignOperator();

private:
    void _MatrixEqualHelper(Matrix4f& m1, Matrix4f& m2);
};

#endif // MatrixTest_h__
