#include <systemc.h>
#include "stim.h"
#include "exor.h"
#include "mon.h"

int sc_main(int argc, char* argv[]) {
    sc_signal<bool> sigA, sigB, sigZ;

    // Declare intermediate signals for the exor module if needed
    sc_signal<bool> h1, h2, h3;

    stim Stim1("Stimulus");
    Stim1.A(sigA);
    Stim1.B(sigB);

    exor DUT("DUT");
    DUT.A(sigA);
    DUT.B(sigB);
    DUT.Y(sigZ);  // Ensure Y matches the exor module's output signal name

    Monitor mon("Monitor");
    mon.A(sigA);
    mon.B(sigB);
    mon.Z(sigZ);

    // Open a VCD trace file
    sc_trace_file *wf = sc_create_vcd_trace_file("exor_waveform");
    sc_trace(wf, sigA, "A");
    sc_trace(wf, sigB, "B");
    sc_trace(wf, sigZ, "Z");

    // Optional: Trace internal signals if available (h1, h2, h3)
    sc_trace(wf, h1, "h1");
    sc_trace(wf, h2, "h2");
    sc_trace(wf, h3, "h3");

    // Start simulation and monitor the waveform
    sc_start(100, SC_NS);  // Run for 100 ns

    // Close the trace file
    sc_close_vcd_trace_file(wf);

    std::cout << "Simulation complete. Trace saved to exor_waveform.vcd" << std::endl;
    return 0;
}
