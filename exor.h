#ifndef EXOR_H
#define EXOR_H

#include <systemc.h>
#include "nand.h"  // We use 4 nand modules to build the XOR

SC_MODULE(exor) {
    sc_in<bool> A, B;
    sc_out<bool> Y;

    // Internal signals for intermediate connections
    sc_signal<bool> h1, h2, h3;

    // Four instances of the nand module
    nand nand1, nand2, nand3, nand4;

    SC_CTOR(exor)
        : nand1("nand1"), nand2("nand2"), nand3("nand3"), nand4("nand4") {
        // Connect nand1 and nand2 to inputs A and B
        nand1.A(A);
        nand1.B(B);
        nand1.Z(h1);

        nand2.A(A);
        nand2.B(h1);
        nand2.Z(h2);

        // nand3 takes B and h2 as input, produces h3
        nand3.A(B);
        nand3.B(h2);
        nand3.Z(h3);

        // nand4 takes h2 and h3 as input and produces Y
        nand4.A(h2);
        nand4.B(h3);
        nand4.Z(Y);
    }
};

#endif  // EXOR_H
