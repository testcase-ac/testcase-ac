#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read M operations
    for (int op = 0; op < M; op++) {
        int l = inf.readInt(1, N, "l");
        inf.readSpace();
        int r = inf.readInt(1, N, "r");
        inf.readEoln();
        ensuref(l <= r,
                "Operation %d has invalid range: l (%d) > r (%d)", op + 1, l, r);
    }

    inf.readEof();
    return 0;
}
