#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>
#include <tlm_utils/multi_passthrough_initiator_socket.h>
#include <cassert>

// Define the SimpleTarget module
#define SIMPLE_INITIATOR_H

using namespace sc_core;
using namespace std;

// Define the SimpleTarget module
class SimpleTarget : public sc_module {
public:
    tlm_utils::simple_target_socket<SimpleTarget> socket;

    SC_CTOR(SimpleTarget) : socket("socket") {
        socket.register_b_transport(this, &SimpleTarget::b_transport);
    }

    void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {
        // Implement the transport functionality here
        cout << "SimpleTarget: Received transaction at address: " 
         << hex << trans.get_address() << endl;
    }
};

// Define the Interconnect module
class Interconnect : public sc_module {
public:
    // Target socket for incoming transactions
    tlm_utils::simple_target_socket<Interconnect> tSocket;
    // Initiator socket for outgoing transactions
    tlm_utils::multi_passthrough_initiator_socket<Interconnect> iSocket;

    // Constructor 
    SC_HAS_PROCESS(Interconnect);
    Interconnect(sc_module_name name, uint64_t memSize, sc_time routingDelay)
        : sc_module(name), _memSize(memSize), _routingDelay(routingDelay) {
        // Register callback for the b_transport interface
        tSocket.register_b_transport(this, &Interconnect::b_transport);
    }

protected:
    uint64_t _memSize; // Size of each memory
    sc_time _routingDelay; // Routing delay

    // TLM-2 blocking transport method
    void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {
        sc_dt::uint64 addr = trans.get_address();
        uint64_t targetId = addr / _memSize;
    
        // Prevent out-of-range access
        if (targetId >= iSocket.size()) {
            SC_REPORT_ERROR("Interconnect", "Invalid memory access: No target for the given address.");
            return;
        }
        
        cout << "Interconnect: Forwarding transaction to Target " 
         << targetId << " at adjusted address: " << (addr % _memSize) << endl;

        addr = addr % _memSize;
        trans.set_address(addr);
        delay += _routingDelay;
        iSocket[targetId]->b_transport(trans, delay);
    }
    
};

class SimpleInitiator : public sc_module {
    public:
        tlm_utils::multi_passthrough_initiator_socket<SimpleInitiator> socket;

        SC_CTOR(SimpleInitiator) : socket("socket") {
            SC_THREAD(thread);
        }

        void thread() {
            tlm::tlm_generic_payload trans;
            sc_time delay = SC_ZERO_TIME;
            //Create a transaction
            trans.set_command(tlm::TLM_READ_COMMAND);
            trans.set_address(0x0C00); //New calculation: 3072 / 1024 = 3
            trans.set_data_length(4);

            cout << "Initiator: Sending transaction to address: " 
            << hex << trans.get_address() << endl;

            //send the transaction
            socket ->b_transport(trans, delay);
        }
    };

// Main function (for example/testing purposes)
int sc_main(int argc, char* argv[]) {
    Interconnect interconnect("Interconnect", 1024, sc_time(10, SC_NS));

    
    //SimpleTarget target0("Target0");
    SimpleTarget target1("Target1");
    SimpleTarget target2("Target2");
    SimpleTarget target3("Target3");
    SimpleTarget target4("Target4");  // New target for 0x1000

    // Bind targets to the interconnect
    //interconnect.iSocket.bind(target0.socket);
    interconnect.iSocket.bind(target1.socket);
    interconnect.iSocket.bind(target2.socket);
    interconnect.iSocket.bind(target3.socket);
    interconnect.iSocket.bind(target4.socket);  // Bind the extra target

    SimpleInitiator initiator("Initiator");
    initiator.socket.bind(interconnect.tSocket);

    sc_start();
    return 0;
}

// Initiator sends a transaction to 0x0C00.
// Interconnect forwards it to Target 3 (since 0x0C00 / 1024 = 3).
//Target 3 successfully receives the transaction.
