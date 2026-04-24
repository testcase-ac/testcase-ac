#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read size of set S
    int L = inf.readInt(1, 50, "L");
    inf.readEoln();

    // Read elements of S
    vector<int> S = inf.readInts(L, 1, 1000, "s_i");
    inf.readEoln();

    // Check for duplicates in S
    sort(S.begin(), S.end());
    for (int i = 1; i < L; i++) {
        ensuref(S[i] != S[i-1],
                "Duplicate elements in S: %d appears at least twice", S[i]);
    }

    // Read n, must satisfy 1 ≤ n ≤ max(S)
    int maxS = S.empty() ? 1 : S.back();
    int n = inf.readInt(1, maxS, "n");
    inf.readEoln();

    inf.readEof();
    return 0;
}
