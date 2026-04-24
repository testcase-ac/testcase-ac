#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read left side species, must be a permutation of 1..N
    vector<char> seenLeft(N+1, false);
    for (int i = 1; i <= N; i++) {
        int x = inf.readInt(1, N, "left");
        inf.readEoln();
        ensuref(!seenLeft[x],
                "Species %d appears multiple times on the left side (at position %d)", x, i);
        seenLeft[x] = true;
    }

    // Read right side species, must be a permutation of 1..N
    vector<char> seenRight(N+1, false);
    for (int i = 1; i <= N; i++) {
        int x = inf.readInt(1, N, "right");
        inf.readEoln();
        ensuref(!seenRight[x],
                "Species %d appears multiple times on the right side (at position %d)", x, i);
        seenRight[x] = true;
    }

    // Ensure every species from 1..N appears exactly once on both sides
    for (int x = 1; x <= N; x++) {
        ensuref(seenLeft[x],  "Species %d is missing on the left side",  x);
        ensuref(seenRight[x], "Species %d is missing on the right side", x);
    }

    inf.readEof();
    return 0;
}
