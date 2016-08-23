#include "UnitTest++/UnitTestPP.h"
#include "EasyLogging/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int, char const *[])
{
    return UnitTest::RunAllTests();
}
