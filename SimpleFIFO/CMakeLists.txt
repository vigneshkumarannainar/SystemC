

project(SimpleFIFO)

# Add the executable
add_executable(SimpleFIFO SimpleFIFO.cpp)

# Include SystemC
target_include_directories(SimpleFIFO PRIVATE $ENV{SYSTEMC_HOME}/include/)

# Link SystemC library
find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(SimpleFIFO PRIVATE ${SYSTEMC_LIBRARY})
