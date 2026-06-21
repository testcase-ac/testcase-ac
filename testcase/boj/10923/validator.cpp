#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    vector<int> seen(n);
    vector<int> s = inf.readInts(n, 0, n - 1, "S_i");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        ensuref(!seen[s[i]], "S is not a permutation: value %d appears more than once", s[i]);
        seen[s[i]] = 1;
    }

    // CHECK: The main statement omits a standalone M bound; the largest stated subtask scale is 30N.
    int m = inf.readInt(0, 30 * n, "M");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int x = inf.readInt(0, n - 1, "X_i");
        inf.readSpace();
        int y = inf.readInt(0, n - 1, "Y_i");
        inf.readEoln();
        (void)x;
        (void)y;
    }

    inf.readEof();
}
