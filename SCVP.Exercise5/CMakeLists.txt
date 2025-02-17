cmake_minimum_required(VERSION 3.10)
project(SCVP_Exercise5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SystemC paths
include_directories(/home/omkar/systemc-install/include)
link_directories(/home/omkar/systemc-install/lib)

# Add the executable
add_executable(exercise5
    main.cpp
    kpn.cpp
)

# Link the SystemC library
target_link_libraries(exercise5 systemc)
