#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // Read initial attractions array A of length N, each 0 or 1
    vector<int> A = inf.readInts(N, 0, 1, "A_i");
    inf.readEoln();

    // Process Q queries
    int cnt_type3 = 0;
    for (int qi = 0; qi < Q; qi++) {
        int t = inf.readInt(1, 3, "type");
        if (t == 1) {
            // Query "1 i"
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
        } else if (t == 2) {
            // Query "2 x"
            inf.readSpace();
            long long x = inf.readLong(1LL, 1000000000LL, "x");
        } else {
            // Query "3"
            cnt_type3++;
        }
        inf.readEoln();
    }

    // There must be at least one type-3 query
    ensuref(cnt_type3 > 0,
            "The input must contain at least one query of type 3, but found none.");

    inf.readEof();
    return 0;
}
