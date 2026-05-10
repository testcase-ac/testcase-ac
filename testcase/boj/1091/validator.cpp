#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(3, 48, "N");
    ensuref(N % 3 == 0, "N (%d) must be a multiple of 3", N);
    inf.readEoln();

    // 2. Read P
    vector<int> P = inf.readInts(N, 0, 2, "P_i");
    inf.readEoln();

    // 3. Read S
    vector<int> S = inf.readInts(N, 0, N-1, "S_i");
    inf.readEoln();

    // 4. Check S is a permutation of 0..N-1
    vector<bool> seen(N, false);
    for (int i = 0; i < N; ++i) {
        ensuref(!seen[S[i]], "S is not a permutation: duplicate value %d at index %d", S[i], i);
        seen[S[i]] = true;
    }

    inf.readEof();
}
