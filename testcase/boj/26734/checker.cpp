#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int n;
vector<int> a;

struct Output {
    int claimedLength;
    bool hasWitness;
};

Output readOutput(InStream& stream, bool requireWitness) {
    int r = stream.readInt(1, n, "R");

    vector<int> indices;
    if (stream.seekEof()) {
        if (requireWitness) {
            stream.quitf(_wa, "missing sequence of selected indices");
        }
        return {r, false};
    }

    indices.reserve(r);
    int previous = 0;
    for (int i = 0; i < r; ++i) {
        int index = stream.readInt(1, n, format("index[%d]", i + 1).c_str());
        if (index <= previous) {
            stream.quitf(_wa,
                         "indices must be strictly increasing: index[%d]=%d after %d",
                         i + 1,
                         index,
                         previous);
        }
        if (!indices.empty() && gcd(a[indices.back()], a[index]) == 1) {
            stream.quitf(_wa,
                         "adjacent selected values at positions %d and %d have gcd 1",
                         indices.back(),
                         index);
        }
        previous = index;
        indices.push_back(index);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after selected indices");
    }
    return {static_cast<int>(indices.size()), true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 30000, "N");
    a.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        a[i] = inf.readInt(1, 100000000, format("A[%d]", i).c_str());
    }

    Output jury = readOutput(ans, false);
    Output participant = readOutput(ouf, true);

    if (participant.claimedLength < jury.claimedLength) {
        quitf(_wa,
              "participant kept fewer elements than jury: participant=%d jury=%d",
              participant.claimedLength,
              jury.claimedLength);
    }
    if (participant.claimedLength > jury.claimedLength) {
        quitf(_fail,
              "participant found a longer stable subsequence: participant=%d jury=%d",
              participant.claimedLength,
              jury.claimedLength);
    }

    quitf(_ok, "stable subsequence length %d", participant.claimedLength);
}
