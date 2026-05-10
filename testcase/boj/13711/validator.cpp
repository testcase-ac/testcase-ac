#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read sequence A
    vector<int> A = inf.readInts(N, 1, N, "A_i");
    inf.readEoln();

    // Read sequence B
    vector<int> B = inf.readInts(N, 1, N, "B_i");
    inf.readEoln();

    // Check that A is a permutation of 1..N
    vector<bool> seenA(N + 1, false);
    for (int i = 0; i < N; ++i) {
        int v = A[i];
        ensuref(!seenA[v], "Duplicate value %d found in sequence A at index %d", v, i + 1);
        seenA[v] = true;
    }
    for (int v = 1; v <= N; ++v) {
        ensuref(seenA[v], "Value %d missing in sequence A", v);
    }

    // Check that B is a permutation of 1..N
    vector<bool> seenB(N + 1, false);
    for (int i = 0; i < N; ++i) {
        int v = B[i];
        ensuref(!seenB[v], "Duplicate value %d found in sequence B at index %d", v, i + 1);
        seenB[v] = true;
    }
    for (int v = 1; v <= N; ++v) {
        ensuref(seenB[v], "Value %d missing in sequence B", v);
    }

    inf.readEof();
}
