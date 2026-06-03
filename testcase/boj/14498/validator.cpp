#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 128, "n");
    inf.readSpace();
    int m = inf.readInt(1, 128, "m");
    inf.readSpace();
    int k = inf.readInt(1, 512, "k");
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        int n_i = inf.readInt(1, n, "n_i");
        inf.readSpace();
        int m_i = inf.readInt(1, m, "m_i");
        inf.readSpace();
        inf.readInt(0, 1, "c_i");
        inf.readEoln();
    }

    inf.readEof();
}
