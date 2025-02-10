// filepath: /home/khaled99/MyRepo/RSLatch/testRSLatch.cpp
#include <systemc.h>
#include "RSLatch.cpp"

int sc_main(int argc, char* argv[])
{
    sc_signal<bool> A, B, D;

    RSLatch rs_latch("RSLatch");
    rs_latch.A(A);
    rs_latch.B(B);
    rs_latch.D(D);

    sc_start(1, SC_NS);

    // Apply test vectors
    A.write(false);
    B.write(false);
    sc_start(1, SC_NS);
    std::cout << "A=0, B=0, D=" << D.read() << std::endl;

    A.write(false);
    B.write(true);
    sc_start(1, SC_NS);
    std::cout << "A=0, B=1, D=" << D.read() << std::endl;

    A.write(true);
    B.write(false);
    sc_start(1, SC_NS);
    std::cout << "A=1, B=0, D=" << D.read() << std::endl;

    A.write(true);
    B.write(true);
    sc_start(1, SC_NS);
    std::cout << "A=1, B=1, D=" << D.read() << std::endl;

    return 0;
}