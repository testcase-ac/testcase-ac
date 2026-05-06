#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T = inf.readInt(1, 400, "T");
    inf.readEoln();

    long long sumN = 0;
    long long sumK = 0;

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 100000, "N");
        inf.readSpace();
        int K = inf.readInt(1, 100, "K");
        inf.readEoln();

        sumN += N;
        sumK += K;

        ensuref(K <= N, "K (%d) must be <= N (%d) at test case %d", K, N, tc);

        vector<int> a = inf.readInts(K, 1, N, "a_i");
        inf.readEoln();

        // Check strictly increasing for a_i
        for (int i = 1; i < K; ++i) {
            ensuref(a[i-1] < a[i], "a_i not strictly increasing at test case %d: a[%d]=%d, a[%d]=%d", tc, i-1, a[i-1], i, a[i]);
        }

        vector<int> b = inf.readInts(K, 1, N, "b_i");
        inf.readEoln();

        // Check strictly increasing for b_i
        for (int i = 1; i < K; ++i) {
            ensuref(b[i-1] < b[i], "b_i not strictly increasing at test case %d: b[%d]=%d, b[%d]=%d", tc, i-1, b[i-1], i, b[i]);
        }
    }

    ensuref(sumN <= 20000000LL, "Sum of N over all test cases exceeds 2e7: %lld", sumN);
    ensuref(sumK <= 20000LL, "Sum of K over all test cases exceeds 2e4: %lld", sumK);

    inf.readEof();
}
