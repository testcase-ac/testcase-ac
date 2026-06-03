#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_T = 100000;
    const int MAX_N = 10000;
    const int MAX_A = 1000000;
    const int MAX_TOTAL_N = 5000000;

    int t = inf.readInt(1, MAX_T, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, MAX_N, "N");
        inf.readEoln();

        totalN += n;
        // CHECK: The statement omits a T bound, so cap total scalar input at the repo's practical size limit.
        ensuref(totalN <= MAX_TOTAL_N, "sum of N exceeds %d", MAX_TOTAL_N);

        vector<int> a = inf.readInts(n, 1, MAX_A, "a_i");
        (void)a;
        inf.readEoln();
    }

    inf.readEof();
}
