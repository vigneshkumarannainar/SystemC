#ifndef KPN_H
#define KPN_H

#include <systemc.h>

SC_MODULE(Add) {
    sc_fifo_in<unsigned int> in1, in2;
    sc_fifo_out<unsigned int> out;

    SC_CTOR(Add) {
        SC_THREAD(process);
    }

    void process();
};

SC_MODULE(Split) {
    sc_fifo_in<unsigned int> in;
    sc_fifo_out<unsigned int> out1, out2, out3;

    SC_CTOR(Split) {
        SC_THREAD(process);
    }

    void process();
};

SC_MODULE(Delay) {
    sc_fifo_in<unsigned int> in;
    sc_fifo_out<unsigned int> out;

    SC_CTOR(Delay) {
        SC_THREAD(process);
    }

    void process();
};

#endif // KPN_H
