#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <systemc.h>

enum base { Start, G, GA, GAA, GAAG };  // State enumeration

SC_MODULE(stateMachine) {
    sc_in<char> input;      // Input: DNA symbol
    sc_in<bool> clk;        // Clock signal

    base current_state;     // Internal state variable

    void process() {
        switch (current_state) {
            case Start:
                if (input.read() == 'G') current_state = G;
                break;
            case G:
                if (input.read() == 'A') current_state = GA;
                else if (input.read() != 'G') current_state = Start;
                break;
            case GA:
                if (input.read() == 'A') current_state = GAA;
                else if (input.read() == 'G') current_state = G;
                else current_state = Start;
                break;
            case GAA:
                if (input.read() == 'G') {
                    current_state = GAAG;
                    std::cout << "Pattern GAAG detected at time " << sc_time_stamp() << std::endl;
                } else if (input.read() == 'A') current_state = GA;
                else current_state = Start;
                break;
            case GAAG:
                current_state = Start;
                break;
        }
    }

    SC_CTOR(stateMachine) : current_state(Start) {
        SC_METHOD(process);
        sensitive << clk.pos();
        dont_initialize();
    }
};

#endif  // End of STATE_MACHINE_H
