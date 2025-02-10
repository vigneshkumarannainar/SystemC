// This is RSLatch code

#ifndef RSLATCH_H
#define RSLATCH_H
// #include "RSlatch.h"
#include <systemc.h>

// RS Latch Module
SC_MODULE(RSlatch) {
    sc_in<bool> A, B;  // Inputs: A (Set), B (Reset)
    sc_out<bool> D;    // Output: D (State)

    sc_signal<bool> C; // Internal signal for feedback

    SC_CTOR(RSlatch) {
        SC_METHOD(process);
        sensitive << A << B << C;  // Update on changes to inputs
    }

    void process() {
        D.write(!(B.read()) && C.read());  // NOR Gate
        C.write(A.read() || D.read());     // NOR Gate (Feedback)
    }
};

#endif // RSLATCH_H
int sc_main(int argc, char* argv[]) {
    // Declare signals
    sc_signal<bool> A, B, D;

    // Instantiate the RS Latch
    RSlatch rs_latch("RS_Latch");

    // Connect signals to module ports
    rs_latch.A(A);
    rs_latch.B(B);
    rs_latch.D(D);

    // Enable waveform tracing
    sc_trace_file *wf = sc_create_vcd_trace_file("RS_Latch_Trace");
    sc_trace(wf, A, "A");
    sc_trace(wf, B, "B");
    sc_trace(wf, D, "D");

    // Start simulation
    sc_start(0, SC_NS);

    // Apply test cases
    cout << "Time: " << sc_time_stamp() << " | A=0, B=0 -> ";
    A.write(0); B.write(0);
    sc_start(5, SC_NS);
    cout << "D=" << D.read() << endl;

    cout << "Time: " << sc_time_stamp() << " | A=1, B=0 -> ";
    A.write(1); B.write(0);
    sc_start(5, SC_NS);
    cout << "D=" << D.read() << endl;

    cout << "Time: " << sc_time_stamp() << " | A=0, B=1 -> ";
    A.write(0); B.write(1);
    sc_start(5, SC_NS);
    cout << "D=" << D.read() << endl;

    cout << "Time: " << sc_time_stamp() << " | A=1, B=1 -> ";
    A.write(1); B.write(1);
    sc_start(5, SC_NS);
    cout << "D=" << D.read() << endl;

    // Close trace file
    sc_close_vcd_trace_file(wf);

    return 0;
}