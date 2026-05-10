#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, m, k
    int n = inf.readInt(1, 20, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    int k = inf.readInt(1, 10, "k");
    inf.readEoln();

    // k must not exceed n, since we choose exactly k jars out of n
    ensuref(k <= n, "k (%d) must be <= n (%d)", k, n);

    // Read m inseparable pairs
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();
        ensuref(a != b,
                "Inseparable pair %d has identical jars: %d and %d",
                i + 1, a, b);
    }

    // No extra data
    inf.readEof();
    return 0;
}
