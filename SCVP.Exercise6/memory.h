#ifndef MEMORY_H
#define MEMORY_H

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>

template <unsigned int SIZE = 1024>
class memory : public sc_module {
public:
    tlm_utils::simple_target_socket<memory> socket;
    unsigned char mem[SIZE];

    SC_CTOR(memory) : socket("socket") {
        socket.register_b_transport(this, &memory::b_transport);
    }

    void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {
        tlm::tlm_command cmd = trans.get_command();
        uint64_t addr = trans.get_address();
        unsigned char* data_ptr = trans.get_data_ptr();

        std::cout << this->name() << ": Accessing memory at address: " << addr << std::endl;

        if (addr >= SIZE) {
            SC_REPORT_FATAL("Memory", "Access out of bounds");
        }

        delay += sc_time(20, SC_NS);

        if (cmd == tlm::TLM_READ_COMMAND) {
            memcpy(data_ptr, &mem[addr], trans.get_data_length());
        } else if (cmd == tlm::TLM_WRITE_COMMAND) {
            memcpy(&mem[addr], data_ptr, trans.get_data_length());
        }

        trans.set_response_status(tlm::TLM_OK_RESPONSE);
        std::cout << this->name() << ": Memory transaction completed." << std::endl;
    }
};

#endif
