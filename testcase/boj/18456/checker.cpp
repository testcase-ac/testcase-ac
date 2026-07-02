#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

int n, k;
vector<int> a;

struct Claim {
    bool possible;
    vector<int> cuts;
};

Claim readClaim(InStream& stream) {
    string verdict = stream.readToken("Yes|No", "verdict");

    Claim claim;
    claim.possible = verdict == "Yes";
    if (!claim.possible) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after No");
        }
        return claim;
    }

    claim.cuts.resize(k - 1);
    int previous = 0;
    for (int i = 0; i < k - 1; ++i) {
        claim.cuts[i] = stream.readInt(1, n - 1, format("b_%d", i + 1).c_str());
        if (claim.cuts[i] <= previous) {
            stream.quitf(_wa, "cut b_%d=%d is not greater than previous cut %d",
                         i + 1, claim.cuts[i], previous);
        }
        previous = claim.cuts[i];
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after split");
    }

    vector<long long> sums(k);
    vector<int> maximums(k);
    int left = 1;
    for (int i = 0; i < k; ++i) {
        int right = (i + 1 == k) ? n : claim.cuts[i];
        for (int position = left; position <= right; ++position) {
            sums[i] += a[position];
            maximums[i] = max(maximums[i], a[position]);
        }
        left = right + 1;
    }

    for (int i = 0; i + 1 < k; ++i) {
        long long diff = llabs(sums[i] - sums[i + 1]);
        int limit = max(maximums[i], maximums[i + 1]);
        if (diff > limit) {
            stream.quitf(_wa,
                         "segments %d and %d violate condition: |%lld-%lld|=%lld > max(%d,%d)=%d",
                         i + 1, i + 2, sums[i], sums[i + 1], diff,
                         maximums[i], maximums[i + 1], limit);
        }
    }

    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        a[i] = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury has a valid split, but participant printed No");
        }
        quitf(_ok, "valid split");
    }

    if (!participant.possible) {
        quitf(_ok, "both outputs claim impossible");
    }
    quitf(_fail, "participant found a valid split while jury claimed impossible");
}
