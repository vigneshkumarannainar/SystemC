#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include "TLM_LT.cpp"

using namespace sc_core;
using namespace std;

// Initiator module generating transactions
struct Initiator : sc_module {
    tlm_utils::simple_initiator_socket<Initiator> socket;

    SC_CTOR(Initiator) : socket("socket") {
        SC_THREAD(thread_process);
    }

    void thread_process() {
        tlm::tlm_generic_payload trans;
        sc_time delay = SC_ZERO_TIME;

        // Generate a write transaction
        trans.set_command(tlm::TLM_WRITE_COMMAND);
        trans.set_address(0);
        int data = 0x12345678;
        trans.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
        trans.set_data_length(4);
        socket->b_transport(trans, delay);

        // Generate a read transaction
        trans.set_command(tlm::TLM_READ_COMMAND);
        trans.set_address(0);
        socket->b_transport(trans, delay);
        cout << "Read data: " << hex << data << endl;
    }
};

// Target module receiving transactions
struct Target : sc_module {
    tlm_utils::simple_target_socket<Target> socket;

    SC_CTOR(Target) : socket("socket") {
        socket.register_b_transport(this, &Target::b_transport);
    }

    void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {
        tlm::tlm_command cmd = trans.get_command();
        sc_dt::uint64 addr = trans.get_address();
        unsigned char* data_ptr = trans.get_data_ptr();

        if (cmd == tlm::TLM_WRITE_COMMAND) {
            cout << "Write to address " << addr << " data " << hex << *reinterpret_cast<int*>(data_ptr) << endl;
        } else if (cmd == tlm::TLM_READ_COMMAND) {
            *reinterpret_cast<int*>(data_ptr) = 0x87654321;
            cout << "Read from address " << addr << " data " << hex << *reinterpret_cast<int*>(data_ptr) << endl;
        }
    }
};

int sc_main(int argc, char* argv[]) {
    Initiator initiator("initiator");
    Target target("target");
    Interconnect interconnect("interconnect", 1024, sc_time(10, SC_NS));

    // Connect initiator and target to the interconnect
    initiator.socket.bind(interconnect.tSocket);
    interconnect.iSocket.bind(target.socket);

    sc_start();
    return 0;
}
