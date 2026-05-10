#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read sequence A of length N
    inf.readInts(N, 1, 1000000000LL, "A");
    inf.readEoln();

    // Read number of queries M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read M queries
    for (int q = 1; q <= M; q++) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        if (type == 1) {
            // Update query: 1 i v
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            long long v = inf.readLong(1LL, 1000000000LL, "v");
            inf.readEoln();
        } else {
            // Range-minimum query: 2 i j
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            int j = inf.readInt(1, N, "j");
            inf.readEoln();
            ensuref(i <= j,
                    "In query %d: for type 2, i (%d) must be <= j (%d)",
                    q, i, j);
        }
    }

    inf.readEof();
    return 0;
}
