#include <systemc.h>
#include "subnet.h"

SC_MODULE(toplevel) {
    subnet s1, s2;

    SC_CTOR(toplevel) : s1("s1"), s2("s2") {
        SC_THREAD(process);
    }

    void process() {
        while (true) {
            wait(10, SC_NS);
            s1.t1.fire();
            wait(10, SC_NS);
            s1.t1.fire();
            wait(10, SC_NS);
            s1.t2.fire();
            wait(10, SC_NS);
            s1.t3.fire();
            wait(10, SC_NS);
            s2.t1.fire();
            wait(10, SC_NS);
            s2.t2.fire();
            sc_stop();
        }
    }
};

int sc_main(int argc, char* argv[]) {
    toplevel t("t");
    sc_start();
    return 0;
}
