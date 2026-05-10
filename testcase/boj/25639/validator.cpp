#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the sequence a[1..N]
    vector<long long> a = inf.readLongs(N, -1000000000LL, 1000000000LL, "a_i");
    inf.readEoln();

    // Read number of queries Q
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    bool hasType2 = false;
    // Process each query
    for (int i = 0; i < Q; i++) {
        // Read query type
        int t = inf.readInt(1, 2, "type");
        inf.readSpace();

        if (t == 1) {
            // Query of form: 1 k x
            int k = inf.readInt(1, N, "k");
            inf.readSpace();
            long long x = inf.readLong(-1000000000LL, 1000000000LL, "x");
        } else {
            // Query of form: 2 l r
            hasType2 = true;
            int l = inf.readInt(1, N, "l");
            inf.readSpace();
            int r = inf.readInt(1, N, "r");
            ensuref(l <= r, "At query %d: expected l <= r, but got l=%d, r=%d", i+1, l, r);
        }

        inf.readEoln();
    }

    // Ensure at least one type-2 query exists
    ensuref(hasType2, "Input must contain at least one query of type 2");

    inf.readEof();
    return 0;
}
