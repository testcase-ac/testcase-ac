#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_T = 100000;
    const int MAX_N = 100000;
    const int MAX_TOTAL_N = 5000000;
    const int MAX_MONEY = 10000;
    const long long MAX_K = 1000000000LL;

    // CHECK: The statement gives no upper bound for T; use the local default.
    int T = inf.readInt(1, MAX_T, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, MAX_N, "N");
        inf.readSpace();
        int M = inf.readInt(1, N, "M");
        inf.readSpace();
        inf.readLong(1LL, MAX_K, "K");
        inf.readEoln();

        totalN += N;
        // CHECK: The statement gives no aggregate size cap across test cases.
        ensuref(totalN <= MAX_TOTAL_N,
                "sum of N exceeds %d at test case %d: %lld",
                MAX_TOTAL_N, tc, totalN);

        vector<int> money = inf.readInts(N, 1, MAX_MONEY, "money_i");
        inf.readEoln();
    }

    inf.readEof();
}
