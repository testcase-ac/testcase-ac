#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int Q = inf.readInt(0, 100000, "Q");
    inf.readEoln();

    // Read and validate Q queries
    for (int i = 0; i < Q; i++) {
        // Read query type: 1 or 2
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            // "1 p x": add x at day p
            inf.readSpace();
            int p = inf.readInt(1, N, "p");
            inf.readSpace();
            long long x = inf.readLong(-2000000000LL, 2000000000LL, "x");
        } else {
            // type == 2: "2 p q": query sum from p to q
            inf.readSpace();
            int p = inf.readInt(1, N, "p");
            inf.readSpace();
            int q = inf.readInt(1, N, "q");
            ensuref(p <= q, "For query %d: p (%d) must be <= q (%d)", i+1, p, q);
        }
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
