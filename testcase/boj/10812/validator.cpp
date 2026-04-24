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
    for (int t = 0; t < M; t++) {
        int i = inf.readInt(1, N, "i");
        inf.readSpace();
        int j = inf.readInt(1, N, "j");
        inf.readSpace();
        int k = inf.readInt(1, N, "k");
        inf.readEoln();

        ensuref(i <= k, "Operation %d: i (%d) must be <= k (%d)", t+1, i, k);
        ensuref(k <= j, "Operation %d: k (%d) must be <= j (%d)", t+1, k, j);
    }

    inf.readEof();
    return 0;
}
