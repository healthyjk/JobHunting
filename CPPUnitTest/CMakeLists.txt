cmake_minimum_required(VERSION 2.8.1)
project(UnitTest++)

option(UTPP_USE_PLUS_SIGN "Set this to OFF if you wish to use '-cpp' instead of '++' in lib/include paths" ON)

if(MSVC14 OR MSVC12)
    # has the support we need
else()
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    if(COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    elseif(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else()
            message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
endif()

# get the main sources
file(GLOB headers_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} UnitTest++/*.h)
file(GLOB sources_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} UnitTest++/*.cpp)
source_group("" FILES ${headers_} ${sources_})

# get platform specific sources
if (WIN32)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    set(platformDir_ Win32)
else()
    set(platformDir_ Posix)
endif(WIN32)

file(GLOB platformHeaders_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} UnitTest++/${platformDir_}/*.h)
file(GLOB platformSources_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} UnitTest++/${platformDir_}/*.cpp)
source_group(${platformDir_} FILES ${platformHeaders_} ${platformSources_})

#include the necessary library
include_directories(.)
include_directories(EasyLogging)

# create the lib
add_library(UnitTest++ STATIC ${headers_} ${sources_} ${platformHeaders_} ${platformSources_})

if(${UTPP_USE_PLUS_SIGN})
	set_target_properties(UnitTest++ PROPERTIES OUTPUT_NAME UnitTest++)
endif()

# add install targets
# need a custom install path?
# define CMAKE_INSTALL_PREFIX to change root folder
if(${UTPP_USE_PLUS_SIGN})
        set (UTPP_INSTALL_DESTINATION "include/UnitTest++")
else()
        set (UTPP_INSTALL_DESTINATION "include/UnitTestPP")
endif()

set(config_install_dir_ lib/cmake/${PROJECT_NAME})
set(targets_export_name_ "${PROJECT_NAME}Targets")

install(TARGETS UnitTest++ EXPORT "${targets_export_name_}" DESTINATION lib)

######################################################################################
#tests Start
######################################################################################
# build the test runner
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/*.cpp tests/*.h tests/*.hpp)
source_group( "" FILES ${TEST_SRCS})
add_executable(TestUnitTest++ ${TEST_SRCS})
target_link_libraries(TestUnitTest++ UnitTest++)
if(${UTPP_USE_PLUS_SIGN})
        set_target_properties(TestUnitTest++ PROPERTIES OUTPUT_NAME TestUnitTest++)
endif()
# run unit tests as post build step
#add_custom_command(TARGET TestUnitTest++
#        POST_BUILD COMMAND TestUnitTest++
#        COMMENT "Running unit tests")
######################################################################################
#tests End
######################################################################################


######################################################################################
#CPPFeatureTest Start
######################################################################################
# build the test runner
file(GLOB CPPTEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CPPFeatureTest/*.cpp CPPFeatureTest/*.h CPPFeatureTest/*.hpp)
file(GLOB CPP_INPUTS_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CPPFeatureTest/*.txt)
source_group( "" FILES ${CPPTEST_SRCS})
add_executable(CPPFeatureTest ${CPPTEST_SRCS})
include_directories(.)
target_link_libraries(CPPFeatureTest UnitTest++)
if(${UTPP_USE_PLUS_SIGN})
        set_target_properties(CPPFeatureTest PROPERTIES OUTPUT_NAME CPPFeatureTest)
endif()
# run unit tests as post build step
#add_custom_command(TARGET CPPFeatureTest
#        POST_BUILD COMMAND CPPFeatureTest
#        COMMENT "Running cppfeatures unit tests")
#install(TARGETS CPPFeatureTest EXPORT "${targets_export_name_}" DESTINATION lib)
######################################################################################
#CPPFeatureTest End
######################################################################################

######################################################################################
#DemosTest Start
######################################################################################
# build the test runner
file(GLOB DEMOSTEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} DemosTest/*.cpp DemosTest/*.h DemosTest/*.hpp)
file(GLOB DEMOS_INPUTS_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} DemosTest/*.txt)
source_group( "" FILES ${DEMOSTEST_SRCS})
add_executable(DemosTest ${DEMOSTEST_SRCS})
include_directories(.)
target_link_libraries(DemosTest UnitTest++)
if(${UTPP_USE_PLUS_SIGN})
        set_target_properties(DemosTest PROPERTIES OUTPUT_NAME DemosTest)
endif()
# run unit tests as post build step
#add_custom_command(TARGET DemosTest
#        POST_BUILD COMMAND DemosTest
#        COMMENT "Running demos unit tests")
#install(TARGETS DemosTest EXPORT "${targets_export_name_}" DESTINATION lib)
######################################################################################
#DemosTest End
######################################################################################


######################################################################################
#UtilsTest Start
######################################################################################
# build the test runner
file(GLOB UTILSTEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} UtilsTest/*.cpp UtilsTest/*.h UtilsTest/*.hpp)
file(GLOB UTILS_INPUTS_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} UtilsTest/*.txt)
source_group( "" FILES ${UTILSTEST_SRCS})
add_executable(UtilsTest ${UTILSTEST_SRCS})
include_directories(.)
target_link_libraries(UtilsTest UnitTest++)
if(${UTPP_USE_PLUS_SIGN})
        set_target_properties(UtilsTest PROPERTIES OUTPUT_NAME UtilsTest)
endif()

# run unit tests as post build step
#add_custom_command(TARGET UtilsTest
#        POST_BUILD COMMAND UtilsTest
#        COMMENT "Running demos unit tests")
#install(TARGETS DemosTest EXPORT "${targets_export_name_}" DESTINATION lib)
######################################################################################
#UtilsTest End
######################################################################################

######################################################################################
#PatternTest Start
######################################################################################
# build the test runner
file(GLOB PATTERN_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} PatternTest/*.cpp PatternTest/*.h PatternTest/*.hpp PatternTest/*/*.h PatternTest/*/*.cpp PatternTest/*/*.hpp)
file(GLOB PATTERN_INPUTS_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} PatternTest/*.txt)
source_group( "" FILES ${PATTERN_SRCS})
add_executable(PatternTest ${PATTERN_SRCS})
include_directories(.)
target_link_libraries(PatternTest UnitTest++)
if(${UTPP_USE_PLUS_SIGN})
        set_target_properties(PatternTest PROPERTIES OUTPUT_NAME PatternTest)
endif()

# run unit tests as post build step
#add_custom_command(TARGET PatternTest
#        POST_BUILD COMMAND PatternTest
#        COMMENT "Running demos unit tests")
######################################################################################
#PatternTest End
######################################################################################

######################################################################################
#AlgorithmTest Start
######################################################################################
# build the test runner
file(GLOB ALGORITHM_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} AlgorithmTest/*.cpp AlgorithmTest/*.h AlgorithmTest/*.hpp)
file(GLOB ALGORITHM_INPUTS_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} AlgorithmTest/*.txt)
source_group( "" FILES ${ALGORITHM_SRCS})
add_executable(AlgorithmTest ${ALGORITHM_SRCS})
include_directories(.)
target_link_libraries(AlgorithmTest UnitTest++)
if(${UTPP_USE_PLUS_SIGN})
        set_target_properties(AlgorithmTest PROPERTIES OUTPUT_NAME AlgorithmTest)
endif()

# run unit tests as post build step
#add_custom_command(TARGET AlgorithmTest
#        POST_BUILD COMMAND AlgorithmTest
#        COMMENT "Running demos unit tests")
######################################################################################
#AlgorithmTest End
######################################################################################


install(FILES ${headers_} DESTINATION ${UTPP_INSTALL_DESTINATION})
install(FILES ${platformHeaders_} DESTINATION ${UTPP_INSTALL_DESTINATION}/${platformDir_})
install(FILES cmake/UnitTest++Config.cmake DESTINATION "${config_install_dir_}")
install(EXPORT "${targets_export_name_}" DESTINATION "${config_install_dir_}")

# copy input file to build dir
file(COPY ${CPP_INPUTS_} DESTINATION .)
file(COPY ${DEMOS_INPUTS_} DESTINATION .)
file(COPY ${UTILS_INPUTS_} DESTINATION .)
file(COPY ${PATTERN_INPUTS_} DESTINATION .)
