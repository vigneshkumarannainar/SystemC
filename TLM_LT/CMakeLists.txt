
project(TLM_LT)

# Add the executable
add_executable(TLM_LT TLM_LT.cpp)

# Include SystemC
target_include_directories(TLM_LT PRIVATE $ENV{SYSTEMC_HOME}/include/)

# Link SystemC library
find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

target_link_libraries(TLM_LT PRIVATE ${SYSTEMC_LIBRARY})