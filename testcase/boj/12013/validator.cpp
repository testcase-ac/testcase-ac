#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 248, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 40, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
