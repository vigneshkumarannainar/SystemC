#include <systemc.h>
#include "nand.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<bool> A, B, Z;  // Signals for NAND module

    nand nand1("NAND1");
    nand1.A(A);
    nand1.B(B);
    nand1.Z(Z);

    // Open a VCD trace file
    sc_trace_file *wf = sc_create_vcd_trace_file("nand_waveform");
    sc_trace(wf, A, "A");
    sc_trace(wf, B, "B");
    sc_trace(wf, Z, "Z");

    // Apply test cases
    A.write(0); B.write(0); sc_start(10, SC_NS);
    A.write(0); B.write(1); sc_start(10, SC_NS);
    A.write(1); B.write(0); sc_start(10, SC_NS);
    A.write(1); B.write(1); sc_start(10, SC_NS);

    // Close the trace file
    sc_close_vcd_trace_file(wf);

    return 0;
}
