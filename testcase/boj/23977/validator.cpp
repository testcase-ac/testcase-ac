#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int K = inf.readInt(1, 39, "K");
    inf.readSpace();
    int N = inf.readInt(2, 8, "N");
    inf.readEoln();

    vector<int> A = inf.readInts(N, 3, 40, "A_i");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < N; ++i) {
        ensuref(seen.insert(A[i]).second, "A_i values must be distinct: duplicate %d", A[i]);
        ensuref(K < A[i], "K must be smaller than every A_i: K=%d, A_%d=%d", K, i + 1, A[i]);
    }

    inf.readEof();
}
