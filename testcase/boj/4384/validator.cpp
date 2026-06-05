#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 450, "weight");
        inf.readEoln();
    }

    inf.readEof();
}
