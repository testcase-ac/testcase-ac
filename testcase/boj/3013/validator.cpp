#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and B
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    inf.readEoln();

    // Read the permutation A of size N
    vector<bool> seen(N+1, false);
    vector<int> A = inf.readInts(N, 1, N, "A_i");
    inf.readEoln();

    // Check that A is a permutation: no duplicates, all in [1..N]
    for (int i = 0; i < N; i++) {
        int v = A[i];
        ensuref(!seen[v],
                "Duplicate value %d found at position %d in the sequence", v, i+1);
        seen[v] = true;
    }
    // (Since values are in [1..N] and no duplicates, it's a valid permutation)

    inf.readEof();
    return 0;
}
