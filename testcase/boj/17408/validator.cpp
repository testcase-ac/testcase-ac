#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read array A of size N
    vector<long long> A = inf.readLongs(N, 1LL, 1000000000LL, "A");
    inf.readEoln();

    // Read number of queries M
    int M = inf.readInt(2, 100000, "M");
    inf.readEoln();

    // Read each query
    for (int qi = 1; qi <= M; ++qi) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            // Update query: 1 i v
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            long long v = inf.readLong(1LL, 1000000000LL, "v");
        } else {
            // Query max sum: 2 l r
            inf.readSpace();
            int l = inf.readInt(1, N, "l");
            inf.readSpace();
            int r = inf.readInt(1, N, "r");
            ensuref(l < r, "In query %d: l (%d) must be < r (%d)", qi, l, r);
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
