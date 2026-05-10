#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // For each rectangle, read and check constraints
    for (int i = 0; i < N; ++i) {
        int x1 = inf.readInt(-10000, 10000, "x_i,1");
        inf.readSpace();
        int y1 = inf.readInt(-10000, 10000, "y_i,1");
        inf.readSpace();
        int x2 = inf.readInt(-10000, 10000, "x_i,2");
        inf.readSpace();
        int y2 = inf.readInt(-10000, 10000, "y_i,2");
        inf.readEoln();

        ensuref(x1 < x2, "Rectangle %d: x_i,1 (%d) must be less than x_i,2 (%d)", i+1, x1, x2);
        ensuref(y1 < y2, "Rectangle %d: y_i,1 (%d) must be less than y_i,2 (%d)", i+1, y1, y2);
    }

    inf.readEof();
}
