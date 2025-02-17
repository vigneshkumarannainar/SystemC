#ifndef SUBNET_H
#define SUBNET_H

#include <systemc.h>
#include "place.h"
#include "transition.h"

SC_MODULE(subnet) {
    place p1, p2, p3, p4;
    transition t1, t2, t3;

    SC_CTOR(subnet) : p1(1), p2(0), p3(0), p4(0),
                      t1("t1"), t2("t2"), t3("t3") {
        t1.in(p1);
        t1.out(p2);
        t2.in(p2);
        t2.out(p3);
        t3.in(p3);
        t3.out(p4);
    }
};

#endif
