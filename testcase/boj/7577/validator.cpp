#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K and N
    int K = inf.readInt(3, 40, "K");
    inf.readSpace();
    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    // Read N probe results
    for (int i = 0; i < N; i++) {
        char buf[20];

        // x_i
        sprintf(buf, "x_%d", i);
        int x = inf.readInt(1, K, buf);
        inf.readSpace();

        // y_i
        sprintf(buf, "y_%d", i);
        int y = inf.readInt(x, K, buf);
        inf.readSpace();

        // r_i
        sprintf(buf, "r_%d", i);
        int r = inf.readInt(0, 1000, buf);

        // implied constraint: r cannot exceed the length of [x, y]
        ensuref(r <= y - x + 1, "r_%d = %d exceeds length of interval [%d,%d] which is %d", i, r, x, y, y - x + 1);

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
