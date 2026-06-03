#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    int rf = inf.readInt(1, n, "r_f");
    inf.readSpace();
    int cf = inf.readInt(1, m, "c_f");
    inf.readSpace();
    int rh = inf.readInt(1, n, "r_h");
    inf.readSpace();
    int ch = inf.readInt(1, m, "c_h");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        vector<int> row = inf.readInts(m, 1, 1000, "a_i_j");
        (void)row;
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
