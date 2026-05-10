#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int M = inf.readInt(2, 100, "M");
    inf.readEoln();

    vector<vector<int>> a(N, vector<int>(M));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            a[i][j] = inf.readInt(0, 2, "cell");
            if (j + 1 < M) inf.readSpace();
        }
        inf.readEoln();
    }

    // Compute minimal brush strokes and ensure it's within reasonable bounds.
    // A simple constructive upper bound: treat each maximal horizontal segment
    // of same non-zero color as a separate stroke.
    long long maxStrokes = 0;
    for (int i = 0; i < N; ++i) {
        int j = 0;
        while (j < M) {
            if (a[i][j] == 0) {
                ++j;
                continue;
            }
            int color = a[i][j];
            ++maxStrokes;
            int k = j + 1;
            while (k < M && a[i][k] == color) ++k;
            j = k;
        }
    }

    // The theoretical maximum under constraints is N * M, but our computed
    // constructive bound should never exceed N*M and is a valid painting.
    long long NM = 1LL * N * M;
    ensuref(maxStrokes <= NM,
            "Computed trivial upper bound on strokes (%lld) exceeds N*M (%lld).",
            maxStrokes, NM);

    inf.readEof();
}
