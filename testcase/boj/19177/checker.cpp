#include "testlib.h"

#include <string>

using namespace std;

struct CaseData {
    int n;
    long long s;
    int k;
};

struct Claim {
    bool possible;
};

static Claim readClaim(InStream& stream, const CaseData& tc, int caseIndex, TResult invalidVerdict) {
    string verdict = stream.readToken("[A-Za-z]+", format("case %d verdict", caseIndex).c_str());

    if (verdict == "NO") {
        return {false};
    }
    if (verdict != "YES") {
        stream.quitf(invalidVerdict,
                     "case %d verdict must be YES or NO, found '%s'",
                     caseIndex,
                     verdict.c_str());
    }

    string bits = stream.readToken("[01]+", format("case %d bitstring", caseIndex).c_str());
    if ((int)bits.size() != tc.n) {
        stream.quitf(invalidVerdict,
                     "case %d bitstring length is %d instead of %d",
                     caseIndex,
                     (int)bits.size(),
                     tc.n);
    }

    int count = 0;
    long long sum = 0;
    for (int i = 0; i < tc.n; ++i) {
        if (bits[i] == '1') {
            ++count;
            sum += i + 1;
        }
    }

    if (count != tc.k) {
        stream.quitf(invalidVerdict,
                     "case %d selects %d clothes instead of %d",
                     caseIndex,
                     count,
                     tc.k);
    }
    if (sum != tc.s) {
        stream.quitf(invalidVerdict,
                     "case %d selected prices sum to %lld instead of %lld",
                     caseIndex,
                     sum,
                     tc.s);
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int tests = inf.readInt();
    for (int caseIndex = 1; caseIndex <= tests; ++caseIndex) {
        CaseData tc;
        tc.n = inf.readInt();
        tc.s = inf.readLong();
        tc.k = inf.readInt();

        Claim jury = readClaim(ans, tc, caseIndex, _fail);
        Claim participant = readClaim(ouf, tc, caseIndex, _wa);

        if (jury.possible && !participant.possible) {
            quitf(_wa,
                  "case %d is possible according to jury, but participant printed NO",
                  caseIndex);
        }
        if (!jury.possible && participant.possible) {
            quitf(_fail,
                  "case %d has a valid participant witness while jury printed NO",
                  caseIndex);
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "all %d case(s) match the jury feasibility claims", tests);
}
