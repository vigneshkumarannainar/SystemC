cmake_minimum_required(VERSION 3.10)
project(SCVP_Exercise6)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SystemC and TLM paths
include_directories(/home/omkar/systemc-install/include)
link_directories(/home/omkar/systemc-install/lib)

# Add executable
add_executable(exercise6 main.cpp)

# Link SystemC library
target_link_libraries(exercise6 systemc)
