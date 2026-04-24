#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, m, l
    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readSpace();
    int l = inf.readInt(1, 1000000000, "l");
    inf.readEoln();

    // Read fish coordinates
    for (int i = 0; i < n; i++) {
        int xi = inf.readInt(1, 1000000000, "x_i");
        inf.readSpace();
        int yi = inf.readInt(1, 1000000000, "y_i");
        inf.readEoln();
    }

    // Read fishermen positions
    vector<int> a = inf.readInts(m, 1, 1000000000, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
