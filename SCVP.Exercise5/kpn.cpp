#include "kpn.h"
#include <iostream>

// Add Process: Reads from in1 and in2, writes the sum to out
void Add::process() {
    while (true) {
        unsigned int a = in1.read();
        unsigned int c = in2.read();
        unsigned int b = a + c;
        out.write(b);
    }
}

// Split Process: Copies input to out1, out2, out3, and prints output
void Split::process() {
    for (int i = 0; i < 10; ++i) {
        unsigned int b = in.read();
        out1.write(b);
        out2.write(b);
        out3.write(b);
        std::cout << "Output e: " << b << std::endl;
    }
    sc_stop();
}

// Delay Process: Reads from in and writes to out
void Delay::process() {
    while (true) {
        unsigned int d = in.read();
        out.write(d);
    }
}
