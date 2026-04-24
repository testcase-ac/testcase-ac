#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of children
    int N = inf.readInt(2, 200, "N");
    inf.readEoln();

    // Read the sequence and verify it's a permutation of 1..N
    vector<bool> seen(N+1, false);
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(1, N, "a_i");
        inf.readEoln();
        ensuref(!seen[x], "Duplicate number at position %d: %d", i+1, x);
        seen[x] = true;
    }

    // Check all numbers from 1 to N appear
    for (int x = 1; x <= N; x++) {
        ensuref(seen[x], "Missing number: %d", x);
    }

    inf.readEof();
    return 0;
}
