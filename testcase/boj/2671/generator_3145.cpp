#include "testlib.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    double p_make_valid = rnd.next(0.0, 1.0);    // probability to make a valid string
    double p_type01    = rnd.next(0.0, 1.0);    // within valid, prob to choose "01" segment
    int maxSegments   = rnd.next(1, 3);         // number of segments for valid base

    // Build a valid string under the regex (100+1+|01)+
    string base = "";
    for (int i = 0; i < maxSegments; i++) {
        if (rnd.next() < p_type01) {
            // segment "01"
            base += "01";
        } else {
            // segment "100+1+"
            int z = rnd.next(2, 3);  // number of zeros >=2
            int o = rnd.next(1, 3);  // number of ones >=1
            base += '1';
            base.append(z, '0');
            base.append(o, '1');
        }
    }

    string output;
    if (rnd.next() < p_make_valid) {
        // produce a valid string
        output = base;
    } else {
        // produce an invalid string by a small mutation
        output = base;
        if (output.empty()) {
            output = "0"; // fallback
        } else {
            if (rnd.next(0,1) == 0 && output.size() >= 1) {
                // flip one bit
                int pos = rnd.next(0, (int)output.size() - 1);
                output[pos] = (output[pos] == '0' ? '1' : '0');
            } else if (output.size() >= 2) {
                // remove one character
                int pos = rnd.next(0, (int)output.size() - 1);
                output.erase(output.begin() + pos);
            } else {
                // flip if too short
                output[0] = (output[0] == '0' ? '1' : '0');
            }
        }
    }

    // Ensure length bound
    if (output.size() > 150) {
        output = output.substr(0, 150);
    }
    println(output);
    return 0;
}
