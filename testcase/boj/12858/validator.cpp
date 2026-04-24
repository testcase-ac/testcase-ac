#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read the sequence of N natural numbers
    vector<int> a = inf.readInts(N, 1, 1000000000, "a_i");
    inf.readEoln();

    // Read number of operations Q
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    bool hasQuery0 = false;
    for (int i = 0; i < Q; i++) {
        // Each operation: T A B
        int T = inf.readInt(0, 1000000000, "T_i");
        inf.readSpace();
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readEoln();

        if (T == 0) {
            hasQuery0 = true;
        }
        ensuref(A <= B,
                "In query %d: A_i (%d) must be <= B_i (%d)",
                i+1, A, B);
    }

    // Ensure at least one GCD query exists
    ensuref(hasQuery0,
            "There must be at least one query with T=0 (GCD query)");

    inf.readEof();
    return 0;
}
