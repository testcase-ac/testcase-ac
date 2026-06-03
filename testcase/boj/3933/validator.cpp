#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCases = 0;
    while (true) {
        int n = inf.readInt(0, 32767, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++testCases;
        ensuref(testCases <= 255, "too many test cases: %d", testCases);
    }

    inf.readEof();
}
