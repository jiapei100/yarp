// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
#include <stdio.h>
#include <yarp/os/all.h>
using namespace yarp::os;

// define the Target class
#include "TargetVer1b.h"

int main() {
    Network::init();
    
    int ct = 0;
    Port p;            // Create a port.
    p.open("/target/raw/out");    // Give it a name on the network.
    while (true) {
        BinPortable<Target> b;        // Make a place to store things.
        b.content().x = ct;
        b.content().y = 42;
        ct++;
        p.write(b);      // Send the data.
        printf("Sent (%d,%d)\n", b.content().x, b.content().y);
        Time::delay(1);
    }

    Network::fini();
    return 0;
}
