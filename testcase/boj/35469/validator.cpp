#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(-1000, 1000, "A_ij");
        for (int j = 1; j < n; ++j) {
            inf.readSpace();
            inf.readInt(-1000, 1000, "A_ij");
        }
        inf.readEoln();
    }

    inf.readEof();
}
