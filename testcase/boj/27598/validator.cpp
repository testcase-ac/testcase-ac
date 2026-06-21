#include "testlib.h"

#include <vector>

using namespace std;

static void readPermutation(int n, const char* name) {
    vector<int> seen(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, n, name);
        ensuref(!seen[x], "%s is not unique: value %d appears more than once", name, x);
        seen[x] = 1;
        if (i < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();

    int sumN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "n");
        inf.readEoln();
        sumN += n;
        ensuref(sumN <= 100000, "sum of n exceeds 100000 after test case %d", tc);

        readPermutation(n, "a_i");
        readPermutation(n, "b_i");
    }

    inf.readEof();
}
