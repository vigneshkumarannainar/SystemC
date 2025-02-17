cmake_minimum_required(VERSION 3.10)
project(SCVP_Exercise3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SystemC paths
include_directories(/home/omkar/systemc-install/include)
link_directories(/home/omkar/systemc-install/lib)

# Include current directory for headers
include_directories(${CMAKE_SOURCE_DIR})

# Add the first executable (state_machine.cpp)
add_executable(state_machine_sim state_machine.cpp)
#add_executable(stimulisim stimuli.cpp)
#add_executable(mainsim main.cpp)
# Link the SystemC library
target_link_libraries(state_machine_sim systemc)
#target_link_libraries(stimulisim systemc)
#target_link_libraries(mainsim systemc)