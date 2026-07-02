#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

const int MAX_VALUE = 1000000;

struct TestCase {
    int n;
    vector<int> a;
};

struct Answer {
    bool possible;
};

vector<TestCase> cases;

Answer readAnswer(InStream& stream, const TestCase& tc, int caseIndex) {
    string verdict = stream.readWord();
    if (verdict == "NO") {
        return {false};
    }
    if (verdict != "YES") {
        stream.quitf(_wa, "case %d verdict must be YES or NO, found '%s'", caseIndex, verdict.c_str());
    }

    vector<int> b(tc.n);
    set<int> usedB;
    for (int i = 0; i < tc.n; ++i) {
        b[i] = stream.readInt(1, MAX_VALUE, format("case %d b[%d]", caseIndex, i + 1).c_str());
        if (!usedB.insert(b[i]).second) {
            stream.quitf(_wa, "case %d has duplicate B value %d", caseIndex, b[i]);
        }
    }

    set<int> sums;
    for (int i = 0; i < tc.n; ++i) {
        for (int j = 0; j < tc.n; ++j) {
            int sum = tc.a[i] + b[j];
            if (!sums.insert(sum).second) {
                stream.quitf(_wa,
                             "case %d has duplicate sum %d from A[%d] + some B value",
                             caseIndex,
                             sum,
                             i + 1);
            }
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    cases.resize(t);
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        TestCase& tc = cases[caseIndex - 1];
        tc.n = inf.readInt();
        tc.a.resize(tc.n);
        for (int i = 0; i < tc.n; ++i) {
            tc.a[i] = inf.readInt();
        }
    }

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        const TestCase& tc = cases[caseIndex - 1];
        Answer jury = readAnswer(ans, tc, caseIndex);
        Answer participant = readAnswer(ouf, tc, caseIndex);

        if (jury.possible && !participant.possible) {
            quitf(_wa, "case %d: jury has a valid YES witness, participant answered NO", caseIndex);
        }
        if (!jury.possible && participant.possible) {
            quitf(_fail, "case %d: participant found a valid YES witness while jury answered NO", caseIndex);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "%d case(s) checked", t);
}
