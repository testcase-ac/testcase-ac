#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    vector<int> p;
};

struct Claim {
    int k;
};

vector<TestCase> tests;

bool isIrreducible(const vector<int>& p) {
    int prefMax = 0;
    for (int i = 1; i + 1 < (int)p.size(); ++i) {
        prefMax = max(prefMax, p[i]);
        if (prefMax == i) {
            return false;
        }
    }
    return true;
}

vector<Claim> readClaims(InStream& stream, TResult invalidStatus) {
    vector<Claim> claims;
    claims.reserve(tests.size());

    for (int tc = 0; tc < (int)tests.size(); ++tc) {
        const TestCase& test = tests[tc];

        int k = stream.readInt(0, test.n - 1, format("K[%d]", tc + 1).c_str());
        vector<int> p = test.p;

        for (int i = 0; i < k; ++i) {
            int s = stream.readInt(1, test.n - 1, format("S[%d][%d]", tc + 1, i + 1).c_str());
            swap(p[s], p[s + 1]);
        }

        if (!isIrreducible(p)) {
            stream.quitf(invalidStatus,
                         "test case %d: applying %d swaps does not produce an irreducible permutation",
                         tc + 1,
                         k);
        }

        claims.push_back({k});
    }

    if (!stream.seekEof()) {
        stream.quitf(invalidStatus, "extra output after all test cases");
    }
    return claims;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    tests.reserve(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = inf.readInt();
        vector<int> p(n + 1);
        for (int i = 1; i <= n; ++i) {
            p[i] = inf.readInt();
        }
        tests.push_back({n, p});
    }

    vector<Claim> jury = readClaims(ans, _fail);
    vector<Claim> participant = readClaims(ouf, _wa);

    for (int tc = 0; tc < t; ++tc) {
        if (participant[tc].k < jury[tc].k) {
            quitf(_fail,
                  "test case %d: participant found fewer swaps than jury: participant=%d jury=%d",
                  tc + 1,
                  participant[tc].k,
                  jury[tc].k);
        }
        if (participant[tc].k > jury[tc].k) {
            quitf(_wa,
                  "test case %d: participant used too many swaps: participant=%d jury=%d",
                  tc + 1,
                  participant[tc].k,
                  jury[tc].k);
        }
    }

    quitf(_ok, "all %d test case(s) have valid minimum-length swap sequences", t);
}
