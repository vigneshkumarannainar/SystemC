#include <systemc.h>
#include "RSLatch.cpp"

SC_MODULE(Testbench)
{
    sc_signal<bool> A;
    sc_signal<bool> B;
    sc_signal<bool> D;

    RSLatch* rs_latch;

    SC_CTOR(Testbench)
    {
        rs_latch = new RSLatch("rs_latch");
        rs_latch->A(A);
        rs_latch->B(B);
        rs_latch->D(D);

        SC_THREAD(test);
    }

    void test()
    {
        // Test vector 1
        A.write(false);
        B.write(false);
        wait(10, SC_NS);
        cout << "A: " << A.read() << " B: " << B.read() << " D: " << D.read() << endl;

        // Test vector 2
        A.write(true);
        B.write(false);
        wait(10, SC_NS);
        cout << "A: " << A.read() << " B: " << B.read() << " D: " << D.read() << endl;

        // Test vector 3
        A.write(false);
        B.write(true);
        wait(10, SC_NS);
        cout << "A: " << A.read() << " B: " << B.read() << " D: " << D.read() << endl;

        // Test vector 4
        A.write(true);
        B.write(true);
        wait(10, SC_NS);
        cout << "A: " << A.read() << " B: " << B.read() << " D: " << D.read() << endl;

        sc_stop();
    }
};

int sc_main(int argc, char* argv[])
{
    Testbench tb("tb");
    sc_start();
    return 0;
}