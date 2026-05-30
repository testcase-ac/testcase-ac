#include "testlib.h"
#include <climits>
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int R = inf.readInt(3, 40, "R");
    inf.readSpace();
    int C = inf.readInt(3, 40, "C");
    inf.readEoln();

    for (int i = 0; i < R; ++i) {
        inf.readInts(C, 0, 255, "V");
        inf.readEoln();
    }

    inf.readInt(INT_MIN, INT_MAX, "T");
    inf.readEoln();

    inf.readEof();
}
