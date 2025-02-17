cmake_minimum_required(VERSION 3.10)
project(SCVP_Exercise4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SystemC paths
include_directories(/home/omkar/systemc-install/include)
link_directories(/home/omkar/systemc-install/lib)

# Add executable only for main.cpp (since the .cpp files for other headers seem to be missing)
add_executable(exercise4
    main.cpp
)

# Link the SystemC library
target_link_libraries(exercise4 systemc)
