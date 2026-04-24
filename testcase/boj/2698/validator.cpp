#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Precompute DP for counts of binary sequences of length i with j adjacent 1's.
    // dp0[i][j]: ending with 0; dp1[i][j]: ending with 1.
    static __int128 dp0[101][101], dp1[101][101], total[101][101];
    // Base for length 1
    dp0[1][0] = 1;
    dp1[1][0] = 1;
    total[1][0] = 2;
    for (int i = 2; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {
            // sequences of length i ending with 0: no new adjacent from last bit
            if (j <= 100) {
                dp0[i][j] = dp0[i-1][j] + dp1[i-1][j];
            }
            // sequences ending with 1: if prev was 0, no new; if prev was 1, we get one new adjacent
            __int128 v = 0;
            v += dp0[i-1][j];
            if (j >= 1) v += dp1[i-1][j-1];
            dp1[i][j] = v;
            total[i][j] = dp0[i][j] + dp1[i][j];
        }
    }

    // Read number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();
    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);
        int n = inf.readInt(1, 100, "n");
        inf.readSpace();
        int k = inf.readInt(1, 100, "k");
        inf.readEoln();

        // Validate the implicit output bound: answer must fit in 32-bit signed
        __int128 ans = 0;
        if (n <= 100 && k <= 100) ans = total[n][k];
        // total[n][k] is defined for all n,k<=100 above
        ensuref(ans <= (__int128)2147483647,
                "Answer for test case %d with (n=%d, k=%d) is %lld which exceeds 2147483647",
                tc, n, k, (long long)ans);
    }

    inf.readEof();
    return 0;
}
