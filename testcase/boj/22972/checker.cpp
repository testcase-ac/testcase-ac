#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int n;
vector<long long> expectedDistances;

struct Claim {
    vector<long long> positions;
};

Claim readClaim(InStream& stream) {
    vector<long long> positions(n);
    for (int i = 0; i < n; ++i) {
        positions[i] = stream.readLong(0LL, 1000000000LL, format("P_%d", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after P_%d", n);
    }

    if (positions[0] != 0) {
        stream.quitf(_wa, "P_1 must be 0, found %lld", positions[0]);
    }
    for (int i = 1; i < n; ++i) {
        if (positions[i - 1] >= positions[i]) {
            stream.quitf(_wa,
                         "positions must be strictly increasing, found P_%d=%lld and P_%d=%lld",
                         i, positions[i - 1], i + 1, positions[i]);
        }
    }

    vector<long long> distances;
    distances.reserve(n * (n - 1) / 2);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            distances.push_back(positions[j] - positions[i]);
        }
    }
    sort(distances.begin(), distances.end());

    if (distances != expectedDistances) {
        int mismatch = -1;
        for (int i = 0; i < static_cast<int>(expectedDistances.size()); ++i) {
            if (distances[i] != expectedDistances[i]) {
                mismatch = i;
                break;
            }
        }
        if (mismatch == -1) {
            stream.quitf(_wa, "distance multiset size mismatch");
        }
        stream.quitf(_wa,
                     "distance multiset mismatch at index %d: expected %lld, found %lld",
                     mismatch + 1, expectedDistances[mismatch], distances[mismatch]);
    }

    return {positions};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    int m = n * (n - 1) / 2;
    expectedDistances.resize(m);
    for (int i = 0; i < m; ++i) {
        expectedDistances[i] = inf.readLong();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    quitf(_ok,
          "valid reconstruction with P_N=%lld; jury P_N=%lld",
          participant.positions.back(), jury.positions.back());
}
