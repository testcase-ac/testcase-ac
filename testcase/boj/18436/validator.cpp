#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read sequence A of length N
    inf.readLongs(N, 1LL, 1000000000LL, "A_i");
    inf.readEoln();

    // Read number of queries M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read M queries
    for (int qi = 1; qi <= M; qi++) {
        int type = inf.readInt(1, 3, "t_i");
        inf.readSpace();
        if (type == 1) {
            // Update query: 1 i x
            int idx = inf.readInt(1, N, "i");
            inf.readSpace();
            long long x = inf.readLong(1LL, 1000000000LL, "x");
            inf.readEoln();
        } else {
            // Count query: 2 l r or 3 l r
            int l = inf.readInt(1, N, "l");
            inf.readSpace();
            int r = inf.readInt(1, N, "r");
            inf.readEoln();
            ensuref(l <= r,
                    "Query %d: l (%d) > r (%d)", qi, l, r);
        }
    }

    inf.readEof();
    return 0;
}
