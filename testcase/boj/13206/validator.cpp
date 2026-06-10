#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no direct T bound; use the local default cap.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000000, "N");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 2000000, "sum of N exceeds 2000000 at case %d", tc);

        vector<int> a = inf.readInts(n, 1, 1000, "A_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
