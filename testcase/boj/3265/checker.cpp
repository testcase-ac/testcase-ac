#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Claim {
    bool impossible;
    vector<int> a;
};

int n, m;
vector<int> b;
vector<int> known;

Claim readClaim(InStream& stream) {
    int first = stream.readInt(-1, n, "first output token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true, {}};
    }
    if (first == 0) {
        stream.quitf(_wa, "A[1] must be between 1 and %d or -1", n);
    }

    vector<int> a(n + 1);
    vector<int> seen(n + 1, 0);
    a[1] = first;
    seen[first] = 1;

    for (int i = 2; i <= n; ++i) {
        a[i] = stream.readInt(1, n, format("A[%d]", i).c_str());
        if (seen[a[i]]) {
            stream.quitf(_wa, "value %d appears more than once", a[i]);
        }
        seen[a[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }

    for (int i = 1; i <= n; ++i) {
        if (known[i] != 0 && a[i] != known[i]) {
            stream.quitf(_wa, "A[%d] is %d, expected known value %d", i, a[i], known[i]);
        }
    }

    int prefixMax = 0;
    for (int i = 1; i <= n; ++i) {
        prefixMax = max(prefixMax, a[i]);
        int actual = (prefixMax == i ? 1 : 0);
        if (actual != b[i]) {
            stream.quitf(_wa, "B[%d] is %d for supplied permutation, expected %d", i, actual, b[i]);
        }
    }

    return {false, a};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    b.assign(n + 1, 0);
    known.assign(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        b[i] = inf.readInt();
    }
    for (int i = 0; i < m; ++i) {
        int x = inf.readInt();
        int y = inf.readInt();
        known[x] = y;
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both jury and participant report no solution");
        }
        quitf(_fail, "participant supplied a valid permutation while jury reports no solution");
    }

    if (participant.impossible) {
        quitf(_wa, "jury has a valid permutation, but participant reports no solution");
    }

    quitf(_ok, "valid permutation");
}
