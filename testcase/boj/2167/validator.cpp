#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(1, 300, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300, "M");
    inf.readEoln();

    // Read the array
    vector<vector<int>> a(N+1, vector<int>(M+1));
    for (int i = 1; i <= N; i++) {
        // Read M integers in [-10000,10000]
        vector<int> row = inf.readInts(M, -10000, 10000, "a");
        for (int j = 1; j <= M; j++) {
            a[i][j] = row[j-1];
        }
        inf.readEoln();
    }

    // Build prefix sums (1-based)
    vector<vector<int64_t>> pref(N+1, vector<int64_t>(M+1, 0));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            pref[i][j] = a[i][j]
                         + pref[i-1][j]
                         + pref[i][j-1]
                         - pref[i-1][j-1];
        }
    }

    // Read K
    int K = inf.readInt(1, 10000, "K");
    inf.readEoln();

    // Process and validate each query
    for (int qi = 1; qi <= K; qi++) {
        int i = inf.readInt(1, N, "i");
        inf.readSpace();
        int j = inf.readInt(1, M, "j");
        inf.readSpace();
        int x = inf.readInt(1, N, "x");
        inf.readSpace();
        int y = inf.readInt(1, M, "y");
        inf.readEoln();

        // Validate order
        ensuref(i <= x, "Query %d: i (%d) > x (%d)", qi, i, x);
        ensuref(j <= y, "Query %d: j (%d) > y (%d)", qi, j, y);

        // Compute region sum
        int64_t sum = pref[x][y] - pref[i-1][y] - pref[x][j-1] + pref[i-1][j-1];
        // Check upper bound as per problem: sum <= 2^31-1
        const int64_t INT32_MAX_LL = 2147483647LL;
        ensuref(sum <= INT32_MAX_LL,
                "Query %d: sum (%lld) exceeds 2^31-1", qi, (long long)sum);
    }

    inf.readEof();
    return 0;
}
