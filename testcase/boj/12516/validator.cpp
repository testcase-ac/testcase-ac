#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "N");
        inf.readEoln();

        vector<int> a = inf.readInts(n, 1, n, "A_i");
        inf.readEoln();

        vector<bool> seen(n + 1, false);
        for (int i = 0; i < n; ++i) {
            ensuref(!seen[a[i]], "value %d appears more than once", a[i]);
            seen[a[i]] = true;
        }
    }

    inf.readEof();
}
