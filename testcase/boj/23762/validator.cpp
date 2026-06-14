#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readLong(1LL, 1000000000LL, "m_i");
    }
    inf.readEoln();
    inf.readEof();
}
