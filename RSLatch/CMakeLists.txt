# filepath: /home/khaled99/MyRepo/RSLatch/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(Exercise2)

# Add the executable
add_executable(RSLatch
    RSLatch.cpp
    testRSLatch.cpp
)

# Include SystemC headers
target_include_directories(RSLatch
    PRIVATE $ENV{SYSTEMC_HOME}/include/
)

# Find the SystemC library
find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

# Link the SystemC library
target_link_libraries(RSLatch
    PRIVATE ${SYSTEMC_LIBRARY}
)