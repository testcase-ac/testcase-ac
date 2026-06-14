#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 100000, "p");
    inf.readEoln();

    for (int i = 0; i < p; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(-1000000000, 1000000000, "integral_i");
    }
    inf.readEoln();

    int a = inf.readInt(-1000000000, 1000000000, "a");
    inf.readSpace();
    int b = inf.readInt(a, 1000000000, "b");
    inf.readEoln();

    inf.readEof();
}
