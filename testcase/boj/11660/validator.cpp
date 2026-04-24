#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1024, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read the N x N grid
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            inf.readInt(1, 1000, "grid");
            if (j < N) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    // Read M queries
    for (int q = 1; q <= M; q++) {
        int x1 = inf.readInt(1, N, "x1");
        inf.readSpace();
        int y1 = inf.readInt(1, N, "y1");
        inf.readSpace();
        int x2 = inf.readInt(1, N, "x2");
        inf.readSpace();
        int y2 = inf.readInt(1, N, "y2");
        inf.readEoln();

        ensuref(x1 <= x2, "Query %d: x1 (%d) must be <= x2 (%d)", q, x1, x2);
        ensuref(y1 <= y2, "Query %d: y1 (%d) must be <= y2 (%d)", q, y1, y2);
    }

    inf.readEof();
    return 0;
}
