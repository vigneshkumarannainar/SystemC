#include <systemc.h>
#include "kpn.h"

int sc_main(int argc, char* argv[]) {
    sc_fifo<unsigned int> fifo_a(10), fifo_b(10), fifo_c(10), fifo_d(10), fifo_e(10);

    // Initialize FIFO b with 1 and c with 0
    fifo_b.write(1);
    fifo_c.write(0);

    Add add("Add");
    add.in1(fifo_a);
    add.in2(fifo_c);
    add.out(fifo_b);

    Split split("Split");
    split.in(fifo_b);
    split.out1(fifo_a);
    split.out2(fifo_d);
    split.out3(fifo_e);

    Delay delay("Delay");
    delay.in(fifo_d);
    delay.out(fifo_c);

    sc_start();
    return 0;
}
