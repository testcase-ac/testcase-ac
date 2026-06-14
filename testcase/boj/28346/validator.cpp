#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for T; cap total scale to keep
    // validation practical under the local numeric-input policy.
    int t = inf.readInt(1, 9000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 500, "N");
        inf.readEoln();

        vector<int> a = inf.readInts(n, 0, 1000000000, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
