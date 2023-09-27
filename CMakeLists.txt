cmake_minimum_required(VERSION 3.20)
project(sfml-demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Find the SFML library
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add your source files
add_executable(sfml-app main.cpp)

# Link SFML libraries to your executable
target_link_libraries(sfml-app sfml-graphics sfml-window sfml-system)