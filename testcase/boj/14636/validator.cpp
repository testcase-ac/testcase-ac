#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m and n
    int m = inf.readInt(1, 500000, "m");
    inf.readSpace();
    int n = inf.readInt(1, 500000, "n");
    inf.readEoln();

    // Read m lines: p_i, d_i
    for (int i = 0; i < m; ++i) {
        int p_i = inf.readInt(1, 1000000000, "p_i");
        inf.readSpace();
        int d_i = inf.readInt(1, 1000000000, "d_i");
        inf.readEoln();
    }

    // Read n lines: q_j, e_j
    for (int j = 0; j < n; ++j) {
        int q_j = inf.readInt(1, 1000000000, "q_j");
        inf.readSpace();
        int e_j = inf.readInt(1, 1000000000, "e_j");
        inf.readEoln();
    }

    inf.readEof();
}
