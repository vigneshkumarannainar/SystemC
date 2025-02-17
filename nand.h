#ifndef NAND_H
#define NAND_H

#include <systemc.h>

SC_MODULE(nand) {
    sc_in<bool> A, B;
    sc_out<bool> Z;

    void do_nand() {
        Z.write(!(A.read() && B.read()));
    }

    SC_CTOR(nand) {
        SC_METHOD(do_nand);
        sensitive << A << B;
    }
};

#endif  // NAND_H
