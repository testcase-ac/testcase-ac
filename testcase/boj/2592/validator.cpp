#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There is exactly one test: ten lines, each a natural number <1000 and a multiple of 10.
    for (int i = 1; i <= 10; i++) {
        // Read the integer on this line
        char name[16];
        sprintf(name, "a_%d", i);
        int x = inf.readInt(10, 990, name);
        // Must be a multiple of 10
        ensuref(x % 10 == 0, "Number %d (%d) is not a multiple of 10", i, x);
        // No extra spaces: line must end here
        inf.readEoln();
    }

    // No extra lines or tokens
    inf.readEof();
    return 0;
}
