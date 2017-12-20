cmake_minimum_required (VERSION 2.6)
project (correlation_skew)

include_directories ( ./main/distribuzioni main/interfaces main/processi main/tools main/termStructures main/pricerEngines main/solvers main/integrals main test cmd)

file(GLOB TESTSOURCES "test/testBoxMuller.cpp")
file(GLOB_RECURSE CORR_SKEW_FILES "main/*.hpp" "main/*.cpp")

find_package(GSL)

set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -Imain/distribuzioni")
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
#add the executable
add_executable (runTestBoxMuller "")# test/testBoxMuller.cpp)
add_executable(cmdCalculateCorrelationSkew "cmd/cmdCalculateCorrelationSkew.cpp")
add_executable(basketPricing "prove/basketPricing.cpp")
add_executable(testBSPricer "test/testBSPricer.cpp")
add_executable(testBasketPricing "test/testBasketPricing.cpp")
add_executable(testJuBasketPricing "test/testJuBasketPricing.cpp")

#add the library
add_library(CorrSkewLib SHARED ${CORR_SKEW_FILES})
target_link_libraries(cmdCalculateCorrelationSkew m gsl gslcblas)
target_link_libraries(CorrSkewLib m gsl gslcblas)
target_link_libraries(basketPricing CorrSkewLib)
target_link_libraries(testBSPricer CorrSkewLib)
target_link_libraries(testBasketPricing CorrSkewLib)
target_link_libraries(testJuBasketPricing CorrSkewLib)

include(main/distribuzioni/CMakeLists.txt)
include(main/tools/CMakeLists.txt)
include(main/pricerEngines/CMakeLists.txt)
include(main/termStructures/CMakeLists.txt)
include(main/processi/CMakeLists.txt)
include(main/interfaces/CMakeLists.txt)
include(main/solvers/CMakeLists.txt)
include(main/integrals/CMakeLists.txt)
include(main/CMakeLists.txt)
include(test/CMakeLists.txt)

#target_sources(runTestBoxMuller PUBLIC main/distribuzioni/randomGenerator.cpp main/distribuzioni/NormalDistribution.cpp)
