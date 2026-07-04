#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    for (int employee = 2; employee <= n; ++employee) {
        int parent = inf.readInt(1, employee - 1, "p_i");
        inf.readEoln();
    }

    inf.readEof();
}
