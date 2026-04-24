#include "testlib.h"
#include <vector>
#include <cinttypes>

using namespace std;

// Reads a memory construction from `stream`, validates it, and returns
// the size of the tree at the reported index P.
// If `stream` == ouf and something is wrong, quits with _wa.
// If `stream` == ans and something is wrong, quits with _fail.
long long readAns(InStream &stream) {
    // Number of non-empty trees V
    int V = stream.readInt(1, 125, "V");
    vector<pair<int,int>> ch(V);
    vector<long long> sz(V, 0);

    // Read each tree's children and compute/check its size
    for (int i = 0; i < V; i++) {
        int L = stream.readInt(-1, i - 1, format("L_%d", i).c_str());
        int R = stream.readInt(-1, i - 1, format("R_%d", i).c_str());
        ch[i] = {L, R};

        long long ls = 0, rs = 0;
        if (L == -1 && R == -1) {
            // leaf
            sz[i] = 1;
        } else {
            if (L != -1) ls = sz[L];
            if (R != -1) rs = sz[R];
            // Check balance: ls == rs or ls == rs + 1
            if (!(ls == rs || ls == rs + 1)) {
                stream.quitf(_wa,
                    "tree %d is not balanced: left size = %" PRId64 ", right size = %" PRId64,
                    i, ls, rs);
            }
            sz[i] = ls + rs;
        }
        // Ensure size is within [0, 1e18]
        if (sz[i] < 0 || sz[i] > 1000000000000000000LL) {
            stream.quitf(_wa,
                "tree %d has invalid size = %" PRId64, i, sz[i]);
        }
    }

    // Read index P of the tree that should have the target size
    int P = stream.readInt(0, V - 1, "P");
    return sz[P];
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt(1, 2000, "T");
    for (int tc = 1; tc <= T; tc++) {
        long long N = inf.readLong(1LL, 1000000000000000000LL, "N");
        long long jans = readAns(ans);
        long long pans = readAns(ouf);
        // Check that contestant's tree size matches jury's
        if (jans != pans) {
            quitf(_wa,
                  "testcase %d: expected tree size = %" PRId64 ", found = %" PRId64,
                  tc, jans, pans);
        }
        // Check that jury's answer indeed satisfies the required N
        if (jans != N) {
            quitf(_fail,
                  "testcase %d: jury's tree size = %" PRId64 " differs from required N = %" PRId64,
                  tc, jans, N);
        }
    }
    quitf(_ok, "All %d testcases passed", T);
    return 0;
}
