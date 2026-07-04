#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound the number of test cases. Use the
    // local default cap for T and a finite aggregate cap for this small-n input.
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 15, "n");
        inf.readEoln();
        totalN += n;
        ensuref(totalN <= 1500000, "sum of n exceeds practical cap: %d", totalN);

        vector<int> seen(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            int book = inf.readInt(1, n, "book");
            ensuref(!seen[book], "book code %d appears more than once", book);
            seen[book] = 1;

            if (i < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
