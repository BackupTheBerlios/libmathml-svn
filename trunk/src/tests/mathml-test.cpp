/**
 * Cpp unit test for libmathml
 **/

#include <cppunit/extensions/HelperMacros.h>
#include "../qmathml/mmlreader.h"
#include "dummypainter.h"
#include <mathml/mmldocument.h>
#include <QDir>
#include <valgrind/valgrind.h>
#include <valgrind/memcheck.h>
#include <string>

// define a unique name for the test here
#define TESTNAME BasicTest

class TESTNAME : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( TESTNAME );
    // add the names of the test functions below here
    CPPUNIT_TEST( testSetGetString );
    CPPUNIT_TEST_SUITE_END();
private:
    int leaked, dubious, reachable, suppressed;
public:
    void setUp() {
        leaked = dubious = reachable = suppressed = 0;
    }
    void tearDown() {
    }
    // add functions with the tests here and use e.g. CPPUNIT_ASSERT to do the
    // test
    void testSetGetString()
    {
        QDir d("/home/oever/testinstalls/share/libmathml/testsuite");
        processDir(d);
        CPPUNIT_ASSERT(VALGRIND_COUNT_ERRORS == 0);
    }
    bool processDir(QDir &dir) {
        QFileInfoList list = dir.entryInfoList();
        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fi = list.at(i);
            if (fi.isDir() && fi.fileName() != "." && fi.fileName() != "..") {
                QDir d(fi.absoluteFilePath());
                if (processDir(d)) {
                    return true;
                }
            } else if (fi.fileName().endsWith(".mml")) {
                QString path = fi.absoluteFilePath();
                testFile(path);
                checkErrors(path);
                if (VALGRIND_COUNT_ERRORS != 0 || leaked != 0) {
                    return true;
                }
            }
        }
        return false;
    }
    void checkErrors(QString &path) {
        if (VALGRIND_COUNT_ERRORS) {
            std::string msg("memory errors for ");
            msg += (const char*)path.toUtf8();
            printf("%s\n", msg.c_str());
        }
        CPPUNIT_ASSERT(VALGRIND_COUNT_ERRORS == 0);
        //VALGRIND_DO_QUICK_LEAK_CHECK;
        //VALGRIND_COUNT_LEAKS(leaked, dubious, reachable, suppressed);
        //CPPUNIT_ASSERT(leaked == 0);
    }
    void testFile(QString &path) {
        printf("%s\n", (const char*)path.toUtf8());
        // parse the file
        QFile f(path);
        DummyPainter *p = new DummyPainter();
        MMLReader *reader = new MMLReader();
        f.open(QIODevice::ReadOnly);
        reader->parse(f);
        f.close();

        MMLDocument *doc = reader->document();
        doc->setPainter(p);
        doc->validate();
        doc->layout();
        doc->paint();
        delete doc;
        delete reader;
        delete p;
    }
};

// register the test
CPPUNIT_TEST_SUITE_REGISTRATION( TESTNAME );
