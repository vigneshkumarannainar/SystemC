#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/tlm_quantumkeeper.h>

class processor : public sc_module {
public:
    tlm_utils::simple_initiator_socket<processor> socket;
    tlm_utils::tlm_quantumkeeper quantum_keeper;

    SC_CTOR(processor) : socket("socket") {
        SC_THREAD(process);
        quantum_keeper.set_global_quantum(sc_time(1000, SC_NS));
        quantum_keeper.reset();
    }

    void process() {
        std::cout << this->name() << ": Starting process thread..." << std::endl;

        for (int i = 0; i < 10; ++i) {
            tlm::tlm_generic_payload trans;
            sc_time delay = quantum_keeper.get_local_time();

            uint64_t addr = (rand() % 1024);
            unsigned char data[4] = {0};

            std::cout << this->name() << ": Executing transaction at address: " << addr << std::endl;

            trans.set_command(tlm::TLM_WRITE_COMMAND);
            trans.set_address(addr);
            trans.set_data_ptr(data);
            trans.set_data_length(4);

            socket->b_transport(trans, delay);

            quantum_keeper.set(delay);
            if (quantum_keeper.need_sync()) {
                std::cout << this->name() << ": Synchronizing quantum..." << std::endl;
                quantum_keeper.sync();
            }
        }
        std::cout << this->name() << ": Process thread completed." << std::endl;
    }
};

#endif
