#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no T bound; use the repo default practical cap.
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalOperations = 0;
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        int k = inf.readInt(0, 1000000, "k");
        inf.readEoln();
        totalOperations += k;
        // CHECK: No aggregate limit is stated, but unbounded T*k is impractical.
        ensuref(totalOperations <= 5000000,
                "total number of operations must not exceed 5000000");

        for (int i = 0; i < k; i++) {
            string op = inf.readToken("[ID]", "op");
            inf.readSpace();
            if (op == "I") {
                inf.readLong(-2147483648LL, 2147483647LL, "n");
            } else {
                int d = inf.readInt(-1, 1, "d");
                ensuref(d == 1 || d == -1,
                        "delete argument at operation %d must be 1 or -1, found %d",
                        i + 1, d);
            }
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
