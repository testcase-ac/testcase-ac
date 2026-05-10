#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read sequence A
    vector<int> A = inf.readInts(N, 0, 1000000, "A_i");
    inf.readEoln();

    // Read sequence B
    vector<int> B = inf.readInts(N, 0, 1000000, "B_i");
    inf.readEoln();

    // Check that A has distinct identifiers
    vector<char> seenA(1000001, 0);
    for (int i = 0; i < N; i++) {
        int a = A[i];
        ensuref(seenA[a] == 0,
                "Duplicate identifier in A at position %d: %d", i+1, a);
        seenA[a] = 1;
    }

    // Check that B has distinct identifiers and matches exactly A's set
    vector<char> seenB(1000001, 0);
    for (int i = 0; i < N; i++) {
        int b = B[i];
        ensuref(seenB[b] == 0,
                "Duplicate identifier in B at position %d: %d", i+1, b);
        ensuref(seenA[b] == 1,
                "Identifier in B at position %d: %d not found in A", i+1, b);
        seenB[b] = 1;
    }

    inf.readEof();
    return 0;
}
