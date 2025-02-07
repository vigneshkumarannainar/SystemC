cmake_minimum_required(VERSION 3.10)

project(Exercise2)

# Remember only one sc_main() function should exist.
# Choose "nand_main.cpp" here to test your NAND implementation.
# Choose "exor_main.cpp" here to test your XOR implementation.

add_executable(My_Repository
    RSLatch.cpp
    #exor_main.cpp
)

target_include_directories(My_Repository
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(My_Repository
    PRIVATE ${SYSTEMC_LIBRARY}
)
