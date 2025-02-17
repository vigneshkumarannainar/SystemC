#include <systemc.h>
#include "memory.h"
#include "bus.h"
#include "processor.h"

int sc_main(int argc, char* argv[]) {
    std::cout << "Simulation started..." << std::endl;

    processor cpu0("cpu0"), cpu1("cpu1");
    memory<512> memory0("memory0"), memory1("memory1");
    bus bus0("bus0");

    // Bind CPU sockets to bus target sockets
    cpu0.socket.bind(bus0.target_socket0);
    cpu1.socket.bind(bus0.target_socket1);

    // Bind bus initiator sockets to memory
    bus0.initiator_socket0.bind(memory0.socket);
    bus0.initiator_socket1.bind(memory1.socket);

    sc_start();

    std::cout << "Simulation ended." << std::endl;
    return 0;
}
