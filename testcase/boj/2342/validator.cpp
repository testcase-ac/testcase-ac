#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int commandCount = 0;
    while (true) {
        int step = inf.readInt(0, 4, "step");
        if (step == 0) {
            break;
        }

        ++commandCount;
        ensuref(commandCount <= 100000,
                "the command sequence length must not exceed 100000");
        inf.readSpace();
    }

    inf.readEoln();
    inf.readEof();
}
