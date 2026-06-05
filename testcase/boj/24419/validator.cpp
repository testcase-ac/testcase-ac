#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 1000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInts(n, 1, 100000, "m_i_j");
        inf.readEoln();
    }

    inf.readEof();
}
