#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T, N, D, K
    int T = inf.readInt(1, 1000000000, "T");
    inf.readSpace();
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int D = inf.readInt(1, 1000000000, "D");
    inf.readSpace();
    int K = inf.readInt(1, 10, "K");
    inf.readEoln();

    // Read a_1 ... a_N
    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        a[i] = inf.readInt(1, T, "a_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    // No further constraints in the problem statement:
    // - a_i can be any value in [1, T], not necessarily sorted, not necessarily unique.

    inf.readEof();
}
