#include "testlib.h"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

string toString(__int128 value) {
    if (value == 0) {
        return "0";
    }
    string result;
    while (value > 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

__int128 readAns(InStream &stream) {
    // Number of non-empty trees V
    int V = stream.readInt(1, 125, "V");
    vector<pair<int,int>> ch(V);
    vector<__int128> sz(V, 0);

    // Read each tree's children and compute/check its size
    for (int i = 0; i < V; i++) {
        int L = stream.readInt(-1, i - 1, format("L_%d", i).c_str());
        int R = stream.readInt(-1, i - 1, format("R_%d", i).c_str());
        ch[i] = {L, R};

        __int128 ls = 0, rs = 0;
        if (L == -1 && R == -1) {
            // leaf
            sz[i] = 1;
        } else {
            if (L != -1) ls = sz[L];
            if (R != -1) rs = sz[R];
            // Check balance: ls == rs or ls == rs + 1
            if (!(ls == rs || ls == rs + 1)) {
                stream.quitf(_wa,
                    "tree %d is not balanced: left size = %s, right size = %s",
                    i, toString(ls).c_str(), toString(rs).c_str());
            }
            sz[i] = ls + rs;
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
        __int128 jans = readAns(ans);
        __int128 pans = readAns(ouf);
        // Check that contestant's tree size matches jury's
        if (jans != pans) {
            quitf(_wa,
                  "testcase %d: expected tree size = %s, found = %s",
                  tc, toString(jans).c_str(), toString(pans).c_str());
        }
        // Check that jury's answer indeed satisfies the required N
        if (jans != N) {
            quitf(_fail,
                  "testcase %d: jury's tree size = %s differs from required N = %lld",
                  tc, toString(jans).c_str(), N);
        }
    }
    quitf(_ok, "All %d testcases passed", T);
    return 0;
}
