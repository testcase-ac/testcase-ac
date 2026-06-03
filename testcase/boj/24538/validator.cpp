#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 1000000, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int s = inf.readInt(1, k, "S_i");
        inf.readSpace();
        int e = inf.readInt(s, k, "E_i");
        inf.readEoln();
    }

    inf.readEof();
}
