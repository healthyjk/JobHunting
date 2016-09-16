#include "UnitTest++/UnitTestPP.h"
#include "EasyLogging/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int, char const *[])
{
    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime-%level-%file-%line: %msg");
    return UnitTest::RunAllTests();
}
