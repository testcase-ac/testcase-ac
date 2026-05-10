#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
#include <limits>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, H
    int N = inf.readInt(0, 200000, "N");
    inf.readSpace();
    int H = inf.readInt(1, 1000000000, "H");
    inf.readEoln();

    // 2. Read N intervals [A_i, B_i]
    vector<pair<int, int>> intervals;
    for (int i = 0; i < N; ++i) {
        int A = inf.readInt(1, H, "A_i");
        inf.readSpace();
        int B = inf.readInt(A, H, "B_i");
        inf.readEoln();
        intervals.emplace_back(A, B);
    }

    // 3. Read Q
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // 4. Read Q T_i
    for (int i = 0; i < Q; ++i) {
        int T = inf.readInt(1, H, "T_i");
        inf.readEoln();
    }

    inf.readEof();
}
