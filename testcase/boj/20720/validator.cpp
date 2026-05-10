#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read n
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    // 2. Read n lines of c_i, a_i, j_i
    for (int i = 0; i < n; ++i) {
        int c_i = inf.readInt(1, 100000, "c_i");
        inf.readSpace();
        int a_i = inf.readInt(1, 100000, "a_i");
        inf.readSpace();
        int j_i = inf.readInt(1, 100000, "j_i");
        inf.readEoln();

        ensuref(a_i <= c_i, "Andy's bid a_i=%d exceeds cost c_i=%d at Pokemon %d", a_i, c_i, i+1);
        ensuref(j_i <= c_i, "Jordan's bid j_i=%d exceeds cost c_i=%d at Pokemon %d", j_i, c_i, i+1);
    }

    // 3. Read b
    int b = inf.readInt(1, 500, "b");
    inf.readEoln();

    // 4. Read b lines of a_j, b_j, c_j
    for (int i = 0; i < b; ++i) {
        int a_j = inf.readInt(1, n, "a_j");
        inf.readSpace();
        int b_j = inf.readInt(1, n, "b_j");
        inf.readSpace();
        int c_j = inf.readInt(1, 100000, "c_j");
        inf.readEoln();
    }

    inf.readEof();
}
