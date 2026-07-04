#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    while (true) {
        int k = inf.readInt(0, 100, "k");
        if (k == 0) {
            inf.readEoln();
            break;
        }

        for (int j = 0; j < k; ++j) {
            inf.readSpace();
            inf.readInt(0, 9999, format("a_%d", j));
        }

        for (int j = 1; j <= k; ++j) {
            inf.readSpace();
            inf.readInt(0, 9999, format("b_%d", j));
        }

        inf.readSpace();
        inf.readInt(0, 999999999, "i");
        inf.readEoln();
    }

    inf.readEof();
}
