#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int h = inf.readInt(2, 200, "h");
        inf.readSpace();
        int c = inf.readInt(2, h, "c");
        inf.readEoln();

        vector<int> x = inf.readInts(h, 0, 1000000, "x_i");
        inf.readEoln();

        for (int i = 1; i < h; ++i) {
            ensuref(x[i - 1] < x[i],
                    "house locations must be strictly increasing: x_%d=%d, x_%d=%d",
                    i,
                    x[i - 1],
                    i + 1,
                    x[i]);
        }
    }

    inf.readEof();
}
