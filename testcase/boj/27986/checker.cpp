#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int n, m;
vector<pair<int, int>> intervals;

struct Claim {
    int k;
};

Claim readClaim(InStream& stream) {
    vector<int> x(n);
    int k = 0;
    for (int i = 0; i < n; ++i) {
        x[i] = stream.readInt(1, n, format("x[%d]", i + 1).c_str());
        k = max(k, x[i]);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d integers", n);
    }

    for (int i = 0; i < m; ++i) {
        const int l = intervals[i].first;
        const int r = intervals[i].second;
        vector<int> seen(k + 1, 0);
        for (int pos = l; pos <= r; ++pos) {
            if (x[pos] <= k) {
                seen[x[pos]] = 1;
            }
        }
        for (int value = 1; value <= k; ++value) {
            if (!seen[value]) {
                stream.quitf(_wa,
                             "interval %d [%d, %d] does not contain value %d for claimed K=%d",
                             i + 1,
                             l + 1,
                             r + 1,
                             value,
                             k);
            }
        }
    }

    return {k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    intervals.resize(m);
    for (int i = 0; i < m; ++i) {
        int l = inf.readInt();
        int r = inf.readInt();
        intervals[i] = {l - 1, r - 1};
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.k < jury.k) {
        quitf(_wa, "jury has better K: jury=%d participant=%d", jury.k, participant.k);
    }
    if (participant.k > jury.k) {
        quitf(_fail, "participant found better K: jury=%d participant=%d", jury.k, participant.k);
    }
    quitf(_ok, "K=%d", participant.k);
}
