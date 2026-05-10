#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 500, "n");
        inf.readEoln();

        vector<int> f = inf.readInts(n, -1000000, 1000000, "f_i");
        inf.readEoln();

        // |f_i| >= 1
        for (int i = 0; i < n; ++i) {
            ensuref(abs(f[i]) >= 1, "f[%d] = %d, but |f_i| must be at least 1", i+1, f[i]);
        }

        vector<vector<int>> deps(n);
        for (int i = 0; i < n; ++i) {
            int x_i = inf.readInt(0, min(300, n-1), "x_i");
            vector<int> dep;
            if (x_i > 0) {
                inf.readSpace();
                dep = inf.readInts(x_i, 1, n, "dep_j");
            }
            inf.readEoln();

            // No self-dependency
            for (int j = 0; j < x_i; ++j) {
                ensuref(dep[j] != i+1, "Bug %d depends on itself", i+1);
            }
            // No duplicates in dependencies
            set<int> s(dep.begin(), dep.end());
            ensuref((int)s.size() == x_i, "Bug %d has duplicate dependencies", i+1);

            deps[i] = dep;
        }

        // No further constraints in statement: cycles are allowed, dependencies can be arbitrary.
    }

    inf.readEof();
}
