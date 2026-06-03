#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    int buffered = 0;
    int informationCount = 0;
    while (true) {
        // CHECK: The statement only says packet numbers are positive integers;
        // cap them at 1e9 to keep the validator within ordinary int input.
        int x = inf.readInt(-1, 1000000000, "x");
        inf.readEoln();

        if (x == -1) {
            break;
        }

        ++informationCount;
        ensuref(informationCount <= 200000,
                "too many information lines: %d", informationCount);

        if (x == 0) {
            ensuref(buffered > 0, "0 command with empty buffer at line %d",
                    informationCount + 1);
            --buffered;
        } else {
            ensuref(x > 0, "command must be positive packet, 0, or -1: %d", x);
            if (buffered < n) {
                ++buffered;
            }
        }
    }

    ensuref(informationCount >= 1, "at least one information line is required");
    inf.readEof();
}
