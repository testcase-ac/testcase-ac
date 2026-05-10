#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(2, 500000, "N");
        inf.readSpace();
        int t = inf.readInt(1, N, "t");
        inf.readSpace();
        int a = inf.readInt(0, N-1, "a");
        inf.readSpace();
        int b = inf.readInt(0, N-1, "b");
        inf.readEoln();

        ensuref(a + b >= N-1, "At test case %d: a + b = %d + %d < N-1 = %d", tc, a, b, N-1);

        vector<int> A = inf.readInts(N, 1, N, "A_i");
        inf.readEoln();

        // Check all A_i are distinct
        set<int> seen;
        for (int i = 0; i < N; ++i) {
            ensuref(seen.insert(A[i]).second, "At test case %d: Duplicate A_i = %d at position %d", tc, A[i], i+1);
        }

        totalN += N;
        ensuref(totalN <= 500000, "Sum of N over all test cases exceeds 500000: currently %lld after test case %d", totalN, tc);
    }

    inf.readEof();
}
