#
# Lines inspired by https://google.github.io/googletest/quickstart-cmake.html
#

# Note: enable_testing() already done in top CMakeLists.txt

add_executable(tests
        GlobalTests.cpp)

target_include_directories(tests
        PRIVATE
        ../src/Include
)
target_link_libraries(tests GTest::gtest_main lib_cppfight sfml-graphics)

# The next two lines enable CMake�s test runner to discover the tests included in the binary,
# using the GoogleTest CMake module.
include(GoogleTest)
gtest_discover_tests(tests)


# Copy resources to build directory
add_dependencies(tests copy-resources)


############################################################################################################


# Note: enable_testing() already done in top CMakeLists.txt

add_executable(EnemyLoaderTests
        EnemyLoaderTests.cpp)

target_include_directories(EnemyLoaderTests
        PRIVATE
        ../src/Include
)
target_link_libraries(EnemyLoaderTests GTest::gtest_main lib_cppfight sfml-graphics)

# The next two lines enable CMake�s test runner to discover the tests included in the binary,
# using the GoogleTest CMake module.
include(GoogleTest)
gtest_discover_tests(EnemyLoaderTests)


# Copy resources to build directory
add_dependencies(EnemyLoaderTests copy-resources)


############################################################################################################

