#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read permutation C of size 2*N
    int M = 2 * N;
    vector<int> C = inf.readInts(M, 1, M, "C");
    inf.readEoln();

    // Check that C is a permutation of 1..2N
    vector<bool> seen(M+1, false);
    for (int i = 0; i < M; i++) {
        int x = C[i];
        ensuref(!seen[x], "Duplicate value %d in C at position %d", x, i+1);
        seen[x] = true;
    }
    for (int v = 1; v <= M; v++) {
        ensuref(seen[v], "Missing value %d in C", v);
    }

    inf.readEof();
    return 0;
}
