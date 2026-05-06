#include "testlib.h"
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: R, C, N, M, S
    int R = inf.readInt(3, 300, "R");
    inf.readSpace();
    int C = inf.readInt(3, 300, "C");
    inf.readSpace();
    int N = inf.readInt(3, C, "N"); // 3 ≤ N ≤ C
    inf.readSpace();
    int M = inf.readInt(0, 300, "M");
    inf.readSpace();
    int S = inf.readInt(1, R - 1, "S"); // 1 ≤ S < R
    inf.readEoln();

    // Second line: a_1 < ... < a_N, all in [1, C]
    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        a[i] = inf.readInt(1, C, "a_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();
    for (int i = 1; i < N; ++i) {
        ensuref(a[i - 1] < a[i],
                "a sequence must be strictly increasing: a[%d]=%d, a[%d]=%d",
                i, a[i - 1], i + 1, a[i]);
    }

    // Third line: b_1 < ... < b_N, all in [1, C]
    vector<int> b(N);
    for (int i = 0; i < N; ++i) {
        b[i] = inf.readInt(1, C, "b_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();
    for (int i = 1; i < N; ++i) {
        ensuref(b[i - 1] < b[i],
                "b sequence must be strictly increasing: b[%d]=%d, b[%d]=%d",
                i, b[i - 1], i + 1, b[i]);
    }

    // Fourth line: t_1 < ... < t_N, all in [1, C]
    vector<int> t(N);
    for (int i = 0; i < N; ++i) {
        t[i] = inf.readInt(1, C, "t_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();
    for (int i = 1; i < N; ++i) {
        ensuref(t[i - 1] < t[i],
                "t sequence must be strictly increasing: t[%d]=%d, t[%d]=%d",
                i, t[i - 1], i + 1, t[i]);
    }

    // Next M lines: puddles (x_j, y_j)
    // Constraints: 1 < x_j < R; 1 ≤ y_j ≤ C
    // All puddle positions distinct.
    set<pair<int,int>> puddles;
    for (int j = 0; j < M; ++j) {
        int xj = inf.readInt(2, R - 1, "x_j"); // 1 < x_j < R
        inf.readSpace();
        int yj = inf.readInt(1, C, "y_j");
        inf.readEoln();

        pair<int,int> p = {xj, yj};
        ensuref(!puddles.count(p),
                "Duplicate puddle position at index %d: (%d, %d)",
                j + 1, xj, yj);
        puddles.insert(p);
    }

    inf.readEof();
}
