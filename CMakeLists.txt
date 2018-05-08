# Retrieved from https://github.com/dmonopoly/gtest-cmake-example/blob/master/CMakeLists.txt
# 2018-05-08

cmake_minimum_required(VERSION 2.8)

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME MyProject)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall")

# This adds another subdirectory, which has 'project(gtest)'.
#add_subdirectory(lib/gtest-1.6.0)

# enable_testing()

# Include the gtest library. gtest_SOURCE_DIR is available due to
# 'project(gtest)' above.
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR})

add_executable(tests test.cpp)

# Standard linking to gtest stuff.
target_link_libraries(tests PUBLIC 
    demy.so
    gtest 
    gtest_main)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable runUnitTests to see those specific tests.
add_test(NAME that-test-I-made COMMAND tests)

# You can also omit NAME and COMMAND. The second argument could be some other
# test executable.
add_test(that-other-test-I-made tests)
