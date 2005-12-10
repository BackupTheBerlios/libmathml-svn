/**
 * This file is the program that runs the unit tests.
 * It is run by calling 'make check'.
 * The code here was taken from these examples:
 * http://cppunit.sourceforge.net/doc/lastest/cppunit_cookbook.html
 **/

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main( int argc, char **argv)
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry
        = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest( registry.makeTest() );
    bool wasSuccessful = runner.run( "", false );
    return wasSuccessful ?0 :1;
}

