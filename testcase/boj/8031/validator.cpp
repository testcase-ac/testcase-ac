#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 40, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(10, 2000000000, "k");
        inf.readEoln();
    }

    inf.readEof();
}
