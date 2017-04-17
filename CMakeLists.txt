cmake_minimum_required(VERSION 3.0)

project(luna CXX)


#==============================================================================#
# Executable                                                                   #
#==============================================================================#
# Find source files
file(GLOB_RECURSE src_cpp src/*.cpp)
file(GLOB_RECURSE src_hpp src/*.hpp)

# Add hpp files to custom tagets to make them appear in files
add_custom_target(src_include SOURCES ${src_hpp})

# Executable
add_executable(${PROJECT_NAME} ${src_cpp})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

#==============================================================================#
# Tests                                                                        #
#==============================================================================#
# Find test files
file(GLOB_RECURSE test_cpp test/*.cpp)
file(GLOB_RECURSE test_hpp test/*.hpp)

# Add hpp files to custom tagets to make them appear in files
add_custom_target(test_include SOURCES ${test_hpp})

# Add executable files
list(APPEND test_cpp ${src_cpp})
list(REMOVE_ITEM test_cpp ${PROJECT_SOURCE_DIR}/src/main.cpp)

# Test executable
add_executable(test_${PROJECT_NAME} ${test_cpp})
set_property(TARGET test_${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
