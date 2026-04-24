#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read N heights, one per line
    for (int i = 1; i <= N; i++) {
        long long h = inf.readLong(1LL, 2000000000LL, "height");
        inf.readEoln();
    }

    // Read sequence S on one line: N integers, 0 <= S[i] <= N-1
    vector<int> S = inf.readInts(N, 0, N-1, "S");
    inf.readEoln();

    // Validate that for each position i (1-based),
    // S[i] <= i-1 (cannot have more people in front than i-1)
    for (int i = 0; i < N; i++) {
        // at position i+1, there are i people before
        ensuref(S[i] <= i,
                "S[%d] = %d is invalid; must be <= %d (number of people before position %d)",
                i+1, S[i], i, i+1);
    }

    inf.readEof();
    return 0;
}
