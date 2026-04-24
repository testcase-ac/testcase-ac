#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Read the permutation of length N
    vector<int> p = inf.readInts(N, 1, N, "permutation");
    inf.readEoln();

    // Check that it's a valid permutation: all values 1..N appear exactly once
    vector<char> seen(N+1, 0);
    for (int i = 0; i < N; i++) {
        int x = p[i];
        ensuref(!seen[x],
                "Duplicate element detected in permutation at position %d: %d",
                i+1, x);
        seen[x] = 1;
    }
    for (int x = 1; x <= N; x++) {
        ensuref(seen[x],
                "Missing element in permutation: %d",
                x);
    }

    inf.readEof();
    return 0;
}
