#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and k
    int N = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int k = inf.readInt(1, N - 1, "k");
    inf.readEoln();

    // Read the sequence A of length N
    vector<int> A = inf.readInts(N, 0, N - 1, "A_i");
    inf.readEoln();

    // Check that A is a permutation of [0, N-1]
    vector<char> seen(N, 0);
    for (int i = 0; i < N; i++) {
        int v = A[i];
        ensuref(!seen[v],
                "Duplicate value detected: A[%d] = %d appears more than once", i + 1, v);
        seen[v] = 1;
    }

    inf.readEof();
    return 0;
}
