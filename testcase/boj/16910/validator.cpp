#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of queries
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    const long long LIM = 1000000000000000000LL;

    for (int i = 0; i < N; i++) {
        // Query type
        int q = inf.readInt(1, 3, "q_i");
        inf.readSpace();
        // Range [l, r]
        long long l = inf.readLong(1LL, LIM, "l_i");
        inf.readSpace();
        long long r = inf.readLong(1LL, LIM, "r_i");
        inf.readEoln();

        // Ensure l <= r
        ensuref(l <= r,
                "Query %d: l_i (%lld) must be <= r_i (%lld)",
                i + 1, l, r);
    }

    inf.readEof();
    return 0;
}
