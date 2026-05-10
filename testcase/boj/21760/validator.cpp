#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Compute total number of games in the league given N, M, k, B
// A = k * B
// Same-league games: per league: M teams, each pair plays A times.
//   Number of unordered pairs per league: M*(M-1)/2
//   Total same-league games across N leagues: N * (M*(M-1)/2) * A
// Cross-league games: choose 2 different leagues out of N, and within them
//   all M*M pairs of teams, each pair plays B times.
//   Number of unordered league pairs: N*(N-1)/2
//   Total cross-league games: (N*(N-1)/2) * (M*M) * B
long long computeTotal(long long N, long long M, long long k, long long B) {
    long long A = k * B;
    __int128 same = (__int128)N * (M * (M - 1LL) / 2LL) * A;
    __int128 cross = (__int128)(N * (N - 1LL) / 2LL) * (M * M) * B;
    __int128 total = same + cross;
    // We only need to know if it's <= 1e9 (D upper bound), so cap at something larger
    long long cap = (long long)2e9;
    if (total > cap) return cap;
    return (long long)total;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        long long N = inf.readLong(2LL, 100LL, "N");
        inf.readSpace();
        long long M = inf.readLong(2LL, 100LL, "M");
        inf.readSpace();
        long long k = inf.readLong(1LL, 100LL, "k");
        inf.readSpace();
        long long D = inf.readLong(1LL, 1000000000LL, "D");
        inf.readEoln();

        // Validate the implied global property:
        // If there exists A = k*B with integers A,B >= 1 such that total games <= D,
        // the answer is max total <= D. If none, output -1.
        // We ensure that our input is such that this property holds:
        // i.e., if minimal total games (B=1) > D, then the only valid answer is -1.
        // That's allowed per statement, so we just must be sure that the minimum games
        // configuration (B=1, hence A=k) is correctly computed and compared to D.
        long long minTotal = computeTotal(N, M, k, 1LL);
        // No extra restriction is stated (inputs where minTotal > D are valid and lead to -1),
        // so there is no need to reject any case here. We just assert our computation
        // doesn't overflow beyond a safe cap (it shouldn't with given constraints).
        ensuref(minTotal >= 0, "Total games must be non-negative");

        // Optionally, we can also check that there exists some B with total <= D implies
        // minTotal <= D, which is logically guaranteed since total grows with B.
        // No further global constraints to enforce.
    }

    inf.readEof();
}
