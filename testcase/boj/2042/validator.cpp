#include "testlib.h"
#include <vector>
#include <climits>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readSpace();
    int K = inf.readInt(1, 10000, "K");
    inf.readEoln();

    // Read initial array
    vector<long long> arr(N+1);
    for (int i = 1; i <= N; i++) {
        char buf[32];
        sprintf(buf, "a_%d", i);
        arr[i] = inf.readLong((long long)LLONG_MIN, (long long)LLONG_MAX, buf);
        inf.readEoln();
    }

    // Fenwick tree for validation: use __int128 to avoid overflow
    vector<__int128_t> fenw(N+1, 0);
    auto fenw_update = [&](int idx, __int128_t delta) {
        for (int i = idx; i <= N; i += i & -i)
            fenw[i] += delta;
    };
    auto fenw_query = [&](int idx) {
        __int128_t s = 0;
        for (int i = idx; i > 0; i -= i & -i)
            s += fenw[i];
        return s;
    };

    // Build tree
    for (int i = 1; i <= N; i++) {
        fenw_update(i, arr[i]);
    }

    // Process M+K operations
    int totalOps = M + K;
    for (int op = 1; op <= totalOps; op++) {
        int type = inf.readInt(1, 2, "a");
        inf.readSpace();
        if (type == 1) {
            // Update
            int b = inf.readInt(1, N, "b");
            inf.readSpace();
            long long c = inf.readLong((long long)LLONG_MIN, (long long)LLONG_MAX, "c");
            inf.readEoln();
            // Apply in validator
            __int128_t delta = ( __int128_t )c - arr[b];
            arr[b] = c;
            fenw_update(b, delta);
        } else {
            // Query
            int b = inf.readInt(1, N, "b");
            inf.readSpace();
            int c = inf.readInt(1, N, "c");
            inf.readEoln();
            ensuref(b <= c, "Invalid query range at operation %d: b=%d > c=%d", op, b, c);
            __int128_t sumR = fenw_query(c);
            __int128_t sumL = fenw_query(b - 1);
            __int128_t result = sumR - sumL;
            // The problem guarantees the answer fits in signed 64-bit
            ensuref(result >= ( __int128_t )LLONG_MIN && result <= ( __int128_t )LLONG_MAX,
                    "Query sum overflow at operation %d: sum out of int64 range", op);
        }
    }

    inf.readEof();
    return 0;
}
