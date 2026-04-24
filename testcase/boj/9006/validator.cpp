#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        // Read n and m
        int n = inf.readInt(1, 1000000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 1000000, "m");
        inf.readEoln();

        // Read left river house positions a_i
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = inf.readInt(-10000000, 10000000, "a_i");
            inf.readEoln();
        }
        // Ensure distinctness on left
        sort(a.begin(), a.end());
        for (int i = 1; i < n; i++) {
            ensuref(a[i] != a[i-1],
                    "Duplicate left river house position at indices %d and %d: value %d",
                    i-1, i, a[i]);
        }

        // Read right river house positions b_j
        vector<int> b(m);
        for (int j = 0; j < m; j++) {
            b[j] = inf.readInt(-10000000, 10000000, "b_j");
            inf.readEoln();
        }
        // Ensure distinctness on right
        sort(b.begin(), b.end());
        for (int j = 1; j < m; j++) {
            ensuref(b[j] != b[j-1],
                    "Duplicate right river house position at indices %d and %d: value %d",
                    j-1, j, b[j]);
        }
    }

    inf.readEof();
    return 0;
}
