#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no explicit T upper bound; use the repo policy cap.
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalK = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int K = inf.readInt(3, 200000, "K");
        inf.readEoln();

        totalK += K;
        // CHECK: The statement has no aggregate input-size cap; avoid impractically huge inputs.
        ensuref(totalK <= 5000000,
                "sum of K over all test cases exceeds practical cap: %lld", totalK);

        inf.readInts(K, 1, 10000, "file_size");
        inf.readEoln();
    }

    inf.readEof();
}
