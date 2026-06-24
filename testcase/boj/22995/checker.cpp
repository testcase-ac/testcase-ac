#include "testlib.h"

#include <vector>

using namespace std;

struct Claim {
    vector<long long> counts;
};

long long countIncreasingSubsequences(const vector<int>& a) {
    vector<long long> dp(a.size(), 1);
    long long total = 0;

    for (int i = 0; i < int(a.size()); ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i]) {
                dp[i] += dp[j];
            }
        }
        total += dp[i];
    }

    return total;
}

Claim readClaim(InStream& stream, const vector<int>& target) {
    Claim claim;
    claim.counts.reserve(target.size());

    for (int tc = 0; tc < int(target.size()); ++tc) {
        int n = stream.readInt(1, 34, format("N[%d]", tc + 1).c_str());
        stream.readEoln();

        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = stream.readInt(1, 1000000000, format("A[%d][%d]", tc + 1, i + 1).c_str());
            if (i + 1 < n) {
                stream.readSpace();
            } else {
                stream.readEoln();
            }
        }

        long long count = countIncreasingSubsequences(a);
        if (count != target[tc]) {
            stream.quitf(_wa,
                         "test case %d has %lld increasing subsequences, expected %d",
                         tc + 1,
                         count,
                         target[tc]);
        }
        claim.counts.push_back(count);
    }

    stream.readEof();
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<int> target(t);
    for (int i = 0; i < t; ++i) {
        target[i] = inf.readInt();
    }

    Claim jury = readClaim(ans, target);
    Claim participant = readClaim(ouf, target);

    for (int i = 0; i < t; ++i) {
        if (participant.counts[i] != jury.counts[i]) {
            quitf(_wa,
                  "test case %d differs from jury: participant=%lld jury=%lld",
                  i + 1,
                  participant.counts[i],
                  jury.counts[i]);
        }
    }

    quitf(_ok, "all %d test cases have valid sequences", t);
}
