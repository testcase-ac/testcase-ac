#include "testlib.h"

#include <vector>
using namespace std;

int n;
int m;

struct Claim {
    vector<long long> a;
};

Claim readClaim(InStream& stream) {
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = stream.readLong(0, 1000000000LL, format("A[%d]", i + 1).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after sequence");
    }
    return {a};
}

void validateClaim(InStream& stream, const Claim& claim) {
    vector<char> seen(m + 1, false);

    for (int l = 0; l < n; ++l) {
        long long sum = 0;
        for (int r = l; r < n; ++r) {
            sum += claim.a[r];
            if (sum > m) {
                stream.quitf(_wa,
                             "subarray [%d, %d] has sum %lld greater than M=%d",
                             l + 1,
                             r + 1,
                             sum,
                             m);
            }
            seen[(int)sum] = true;
        }
    }

    for (int x = 0; x <= m; ++x) {
        if (!seen[x]) {
            stream.quitf(_wa, "no subarray has sum %d", x);
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();

    Claim jury = readClaim(ans);
    validateClaim(ans, jury);

    Claim participant = readClaim(ouf);
    validateClaim(ouf, participant);

    quitf(_ok, "valid sequence");
}
