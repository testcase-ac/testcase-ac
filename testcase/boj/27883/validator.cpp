#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 7400, "n");
    inf.readSpace();
    int m = inf.readInt(1, 7400, "m");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        inf.readInt(1, n - 1, "answer");
        inf.readEoln();
    }

    inf.readEof();
}
