#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readSpace();
        inf.readInt(1, 10000, "c_i");
        inf.readEoln();

        ensuref(a != b, "warp %d connects room %d to itself", i, a);
    }

    inf.readInts(n, 1, 10000, "t_i");
    inf.readEoln();
    inf.readEof();
}
