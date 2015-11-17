#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

int main()
{
    CppUnit::TestResult r;
    CppUnit::TestResultCollector rc;
    r.addListener(&rc);

    CppUnit::TestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    runner.run(r);

    CppUnit::TextOutputter o(&rc, std::cout);
    o.write();

    return rc.wasSuccessful()?0:1;
}