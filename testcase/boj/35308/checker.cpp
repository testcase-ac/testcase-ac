#include "testlib.h"

#include <vector>

using namespace std;

struct TestCase {
    int n;
    int k;
};

struct Claim {
    bool impossible;
};

vector<TestCase> cases;

Claim readClaim(InStream& stream, const TestCase& tc, int caseIdx) {
    setTestCase(caseIdx);

    int first = stream.readInt(-1, tc.n, "first output token");
    if (first == -1) {
        stream.readEoln();
        return {true};
    }
    if (first == 0) {
        stream.quitf(_wa, "case %d: first permutation value is 0", caseIdx);
    }

    vector<int> p(tc.n + 1);
    vector<int> seen(tc.n + 1, 0);
    p[1] = first;
    seen[first] = 1;

    for (int i = 2; i <= tc.n; ++i) {
        stream.readSpace();
        p[i] = stream.readInt(1, tc.n, format("P[%d]", i).c_str());
        if (seen[p[i]]) {
            stream.quitf(_wa, "case %d: value %d appears more than once", caseIdx, p[i]);
        }
        seen[p[i]] = 1;
    }
    stream.readEoln();

    if (p[1] != tc.k) {
        stream.quitf(_wa, "case %d: P[1]=%d, expected K=%d", caseIdx, p[1], tc.k);
    }

    int current = p[1];
    for (int i = 2; i <= tc.n; ++i) {
        current = p[current];
        if (current != p[i]) {
            stream.quitf(_wa,
                         "case %d: after %d applications value is %d, but P[%d]=%d",
                         caseIdx,
                         i - 1,
                         current,
                         i,
                         p[i]);
        }
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    cases.resize(t + 1);
    for (int caseIdx = 1; caseIdx <= t; ++caseIdx) {
        cases[caseIdx].n = inf.readInt();
        cases[caseIdx].k = inf.readInt();
    }

    for (int caseIdx = 1; caseIdx <= t; ++caseIdx) {
        Claim jury = readClaim(ans, cases[caseIdx], caseIdx);
        Claim participant = readClaim(ouf, cases[caseIdx], caseIdx);

        if (jury.impossible && !participant.impossible) {
            quitf(_fail, "case %d: participant produced a valid witness while jury says -1", caseIdx);
        }
        if (!jury.impossible && participant.impossible) {
            quitf(_wa, "case %d: participant says -1 but jury has a valid witness", caseIdx);
        }
    }

    ans.readEof();
    ouf.readEof();
    quitf(_ok, "all %d case(s) match the jury feasibility claims", t);
}
