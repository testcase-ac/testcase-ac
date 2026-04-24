#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, d, k, c
    int N = inf.readInt(2, 30000, "N");
    inf.readSpace();
    int d = inf.readInt(2, 3000, "d");
    inf.readSpace();
    int k = inf.readInt(2, 3000, "k");
    inf.readSpace();
    int c = inf.readInt(1, d, "c");
    inf.readEoln();

    // k must not exceed N
    ensuref(k <= N, "Constraint violation: k (%d) must be <= N (%d)", k, N);

    // Read N lines of sushi types
    for (int i = 0; i < N; i++) {
        inf.readInt(1, d, "sushi_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
