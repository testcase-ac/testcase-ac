#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 40, "N");
    inf.readEoln();

    // Read M
    int M = inf.readInt(0, N, "M");
    inf.readEoln();

    // Read VIP seats, must be sorted ascending and unique
    vector<int> vip;
    vip.reserve(M);
    int prev = 0;
    for (int i = 0; i < M; i++) {
        int seat = inf.readInt(1, N, "VIP");
        inf.readEoln();
        ensuref(seat > prev,
                "VIP seats must be strictly increasing: VIP[%d]=%d is not > previous %d",
                i, seat, prev);
        vip.push_back(seat);
        prev = seat;
    }

    // Compute number of ways and check it's <= 2e9
    // DP: dp[i] = number of ways to arrange i free seats in a row (swap with adjacent)
    // dp[0]=1, dp[1]=1, dp[i]=dp[i-1]+dp[i-2]
    vector<long long> dp(N+2);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= N; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    long long answer = 1;
    prev = 0;
    for (int s : vip) {
        int len = s - prev - 1;
        // multiply by dp[len]
        answer *= dp[len];
    prev = s;
    }
    // Last segment after last VIP
    int lastLen = N - prev;
    answer *= dp[lastLen];

    ensuref(answer <= 2000000000LL,
            "Number of seating arrangements exceeds 2e9: %lld", answer);

    inf.readEof();
    return 0;
}
