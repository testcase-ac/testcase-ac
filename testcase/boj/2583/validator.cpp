#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M, N, K
    int M = inf.readInt(1, 100, "M");
    inf.readSpace();
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100, "K");
    inf.readEoln();

    // Prepare grid to mark covered cells
    vector< vector<bool> > covered(M, vector<bool>(N, false));

    // Read rectangles and mark interiors
    for (int i = 0; i < K; i++) {
        int x1 = inf.readInt(0, N, "x1");
        inf.readSpace();
        int y1 = inf.readInt(0, M, "y1");
        inf.readSpace();
        int x2 = inf.readInt(0, N, "x2");
        inf.readSpace();
        int y2 = inf.readInt(0, M, "y2");
        inf.readEoln();

        // Validate rectangle coordinates
        ensuref(x1 < x2,
                "Rectangle %d: x1 (%d) must be strictly less than x2 (%d)",
                i, x1, x2);
        ensuref(y1 < y2,
                "Rectangle %d: y1 (%d) must be strictly less than y2 (%d)",
                i, y1, y2);

        // Mark interior cells (x in [x1, x2), y in [y1, y2))
        for (int y = y1; y < y2; y++) {
            for (int x = x1; x < x2; x++) {
                covered[y][x] = true;
            }
        }
    }

    // Ensure at least one cell remains uncovered (input guarantee)
    long long total = 1LL * M * N;
    long long cnt = 0;
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < N; x++) {
            if (covered[y][x]) cnt++;
        }
    }
    ensuref(cnt < total,
            "All %lld cells are covered by rectangles; at least one must remain",
            total);

    inf.readEof();
    return 0;
}
