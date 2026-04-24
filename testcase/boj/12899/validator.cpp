#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of queries N
    int N = inf.readInt(1, 2000000, "N");
    inf.readEoln();

    // Maintain current size of the multiset S
    long long curr_size = 0;

    for (int i = 0; i < N; i++) {
        // Read query type T
        int T = inf.readInt(1, 2, "T");
        inf.readSpace();
        // Read X with appropriate bounds
        int X;
        if (T == 1) {
            // For insertion, X must be between 1 and 2e6
            X = inf.readInt(1, 2000000, "X");
        } else {
            // For deletion by rank, X must be at least 1 and at most N
            X = inf.readInt(1, N, "X");
        }
        inf.readEoln();

        // Check global property: when T==2, there must be at least X elements
        if (T == 1) {
            curr_size++;
        } else {
            ensuref(curr_size >= X,
                    "Not enough elements for type-2 query at line %d: current size = %lld, X = %d",
                    i + 2, curr_size, X);
            curr_size--;
        }
    }

    inf.readEof();
    return 0;
}
