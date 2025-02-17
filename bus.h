#ifndef BUS_H
#define BUS_H

#include <systemc.h>
#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>
#include <tlm_utils/simple_initiator_socket.h>

class bus : public sc_module {
public:
    tlm_utils::simple_target_socket<bus> target_socket0;
    tlm_utils::simple_target_socket<bus> target_socket1;
    tlm_utils::simple_initiator_socket<bus> initiator_socket0;
    tlm_utils::simple_initiator_socket<bus> initiator_socket1;

    SC_CTOR(bus) : target_socket0("target_socket0"), target_socket1("target_socket1"),
                   initiator_socket0("initiator_socket0"), initiator_socket1("initiator_socket1") {
        target_socket0.register_b_transport(this, &bus::b_transport_0);
        target_socket1.register_b_transport(this, &bus::b_transport_1);
    }

    void b_transport_0(tlm::tlm_generic_payload& trans, sc_time& delay) {
        route_transaction(trans, delay);
    }

    void b_transport_1(tlm::tlm_generic_payload& trans, sc_time& delay) {
        route_transaction(trans, delay);
    }

    void route_transaction(tlm::tlm_generic_payload& trans, sc_time& delay) {
        uint64_t addr = trans.get_address();

        std::cout << "Bus: Routing transaction at address: " << addr << std::endl;

        if (addr < 512) {
            initiator_socket0->b_transport(trans, delay);
        } else if (addr < 1024) {
            trans.set_address(addr - 512);
            initiator_socket1->b_transport(trans, delay);
        } else {
            SC_REPORT_FATAL("Bus", "Address out of range");
        }
    }
};

#endif
