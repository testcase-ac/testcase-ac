#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of wires N: 1 <= N <= 100000
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Positions go up to 500000; ensure uniqueness on both poles
    const int MAXP = 500000;
    vector<char> seenA(MAXP+1, 0), seenB(MAXP+1, 0);

    for (int i = 0; i < n; i++) {
        int a = inf.readInt(1, MAXP, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, MAXP, "b_i");
        inf.readEoln();

        ensuref(!seenA[a],
                "Duplicate A pole connection at wire index %d: position %d", i+1, a);
        ensuref(!seenB[b],
                "Duplicate B pole connection at wire index %d: position %d", i+1, b);

        seenA[a] = 1;
        seenB[b] = 1;
    }

    inf.readEof();
    return 0;
}
