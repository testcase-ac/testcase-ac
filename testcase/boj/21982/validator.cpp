#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// We will also verify that generated H[i], W[i] stay in [1, 1e9] as promised.

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int n = inf.readInt(2, 5000000, "n");
        inf.readSpace();
        long long X = inf.readLong(1LL, 1000000000LL, "X");
        inf.readEoln();

        long long h_s = inf.readLong(1LL, 1000000000LL, "h_s");
        inf.readSpace();
        long long h_a = inf.readLong(1LL, 1000000000LL, "h_a");
        inf.readSpace();
        long long h_b = inf.readLong(1LL, 1000000000LL, "h_b");
        inf.readSpace();
        long long h_c = inf.readLong(1LL, 1000000000LL, "h_c");
        inf.readEoln();

        long long w_s = inf.readLong(1LL, 1000000000LL, "w_s");
        inf.readSpace();
        long long w_a = inf.readLong(1LL, 1000000000LL, "w_a");
        inf.readSpace();
        long long w_b = inf.readLong(1LL, 1000000000LL, "w_b");
        inf.readSpace();
        long long w_c = inf.readLong(1LL, 1000000000LL, "w_c");
        inf.readEoln();

        // Now validate the implied constraints about sequences H[i], W[i]:
        //  - 1 <= H[i], W[i] <= 1e9 for all i
        //  - H is strictly increasing.
        // We generate them using 64-bit to avoid overflow.

        vector<long long> H(n), W(n);

        // i = 0
        {
            long long H0 = (h_s % h_c) + 1;
            long long W0 = (w_s % w_c) + 1;
            H[0] = H0;
            W[0] = W0;
            ensuref(1LL <= H0 && H0 <= 1000000000LL,
                    "H[0]=%lld out of bounds [1,1e9]", H0);
            ensuref(1LL <= W0 && W0 <= 1000000000LL,
                    "W[0]=%lld out of bounds [1,1e9]", W0);
        }

        for (int i = 1; i < n; ++i) {
            // H[i] = H[i-1] + 1 + ( (H[i-1] * h_a + h_b) % h_c )
            __int128 tmpH = (__int128)H[i-1] * (__int128)h_a + (__int128)h_b;
            long long modH = (long long)(tmpH % h_c);
            long long Hi = H[i-1] + 1 + modH;

            // W[i] = (W[i-1] * w_a + w_b) % w_c + 1
            __int128 tmpW = (__int128)W[i-1] * (__int128)w_a + (__int128)w_b;
            long long modW = (long long)(tmpW % w_c);
            long long Wi = modW + 1;

            H[i] = Hi;
            W[i] = Wi;

            ensuref(1LL <= Hi && Hi <= 1000000000LL,
                    "H[%d]=%lld out of bounds [1,1e9]", i, Hi);
            ensuref(1LL <= Wi && Wi <= 1000000000LL,
                    "W[%d]=%lld out of bounds [1,1e9]", i, Wi);

            ensuref(Hi > H[i-1],
                    "H is not strictly increasing at index %d: H[%d]=%lld, H[%d]=%lld",
                    i, i-1, H[i-1], i, Hi);
        }

        // Done with this test case
    }

    inf.readEof();
}
