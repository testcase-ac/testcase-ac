#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and Q
    int N = inf.readInt(1, 250000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 250000, "Q");
    inf.readEoln();

    // 2. Read N intervals [l_i, r_i]
    vector<pair<int, int>> intervals(N);
    for (int i = 0; i < N; ++i) {
        int l = inf.readInt(1, 1000000, "l_i");
        inf.readSpace();
        int r = inf.readInt(1, 1000000, "r_i");
        inf.readEoln();
        ensuref(l < r, "Interval %d: l_i (%d) must be less than r_i (%d)", i+1, l, r);
        intervals[i] = {l, r};
    }

    // 3. Read Q laser intervals [s_j, e_j]
    for (int j = 0; j < Q; ++j) {
        int s = inf.readInt(1, 1000000, "s_j");
        inf.readSpace();
        int e = inf.readInt(1, 1000000, "e_j");
        inf.readEoln();
        ensuref(s < e, "Laser %d: s_j (%d) must be less than e_j (%d)", j+1, s, e);
    }

    inf.readEof();
}
