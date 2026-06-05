#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 5, "day");
        inf.readEoln();
    }

    inf.readEof();
}
