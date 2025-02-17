cmake_minimum_required(VERSION 3.10)
project(Exercise8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SystemC paths
include_directories(/home/omkar/systemc-install/include)
link_directories(/home/omkar/systemc-install/lib)

# Add the executable
add_executable(exercise8
    main.cpp
    memory_manager.cpp
)

# Link the SystemC library
target_link_libraries(exercise8 systemc)
