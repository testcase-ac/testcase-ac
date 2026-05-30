#include "testlib.h"
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N = 9;
    const int STEPS = 81;

    for (int step = 0; step < STEPS; ++step) {
        inf.readInt(1, N, "r");
        inf.readSpace();
        inf.readInt(1, N, "c");
        inf.readSpace();
        inf.readInt(1, N, "v");
        inf.readEoln();
    }

    inf.readEof();
}
