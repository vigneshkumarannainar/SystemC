#include <iostream>

#include "state_machine.h"
#include <systemc.h>

int sc_main(int argc, char* argv[]) {
    sc_signal<char> input;
    sc_clock clk("clk", 10, SC_NS);  // Clock with 10 ns period

    stateMachine sm("StateMachine");
    sm.input(input);
    sm.clk(clk);

    // Apply test sequence: "G", "A", "A", "G", "C", "G", "A", "A", "G"
    char dna_sequence[] = {'G', 'A', 'A', 'G', 'C', 'G', 'A', 'A', 'G'};
    //char dna_sequence[] = {'G', 'A', 'G', 'A', 'G', 'G', 'A', 'A', 'G'};

    int sequence_length = sizeof(dna_sequence) / sizeof(dna_sequence[0]);

    for (int i = 0; i < sequence_length; i++) {
        input.write(dna_sequence[i]);
        sc_start(10, SC_NS);  // Advance simulation by one clock cycle
    }

    return 0;
}

// TODO