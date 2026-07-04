#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 300000, "M");
    inf.readEoln();

    vector<int> t = inf.readInts(n, 1, 3, "T_i");
    inf.readEoln();

    for (int j = 1; j <= m; ++j) {
        int a = inf.readInt(1, n, "A_j");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_j");
        inf.readSpace();
        int c = inf.readInt(1, n, "C_j");
        inf.readEoln();

        ensuref(a != b, "A_j and B_j must differ at row %d: %d", j, a);
        ensuref(a != c, "A_j and C_j must differ at row %d: %d", j, a);
        ensuref(b != c, "B_j and C_j must differ at row %d: %d", j, b);
    }

    inf.readEof();
}
