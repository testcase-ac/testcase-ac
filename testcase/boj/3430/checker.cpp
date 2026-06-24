#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct TestCase {
    int n;
    vector<int> forecast;
};

struct Claim {
    bool possible;
};

vector<TestCase> cases;

Claim readClaim(InStream& stream, const TestCase& tc, int caseIndex) {
    string verdict = stream.readWord("YES|NO", format("case %d verdict", caseIndex).c_str());
    if (verdict == "NO") {
        return {false};
    }

    vector<char> full(tc.n + 1, 1);
    int dryDayIndex = 0;
    for (int day = 0; day < (int)tc.forecast.size(); ++day) {
        int lake = tc.forecast[day];
        if (lake == 0) {
            ++dryDayIndex;
            int drink = stream.readInt(0, tc.n,
                                       format("case %d dry action %d", caseIndex, dryDayIndex).c_str());
            if (drink != 0) {
                if (!full[drink]) {
                    stream.quitf(_wa,
                                 "case %d dry action %d drinks from empty lake %d",
                                 caseIndex, dryDayIndex, drink);
                }
                full[drink] = 0;
            }
        } else {
            if (full[lake]) {
                stream.quitf(_wa,
                             "case %d overflows at day %d on lake %d",
                             caseIndex, day + 1, lake);
            }
            full[lake] = 1;
        }
    }

    return {true};
}

vector<Claim> readAllClaims(InStream& stream) {
    vector<Claim> claims;
    claims.reserve(cases.size());
    for (int i = 0; i < (int)cases.size(); ++i) {
        claims.push_back(readClaim(stream, cases[i], i + 1));
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after case %d", (int)cases.size());
    }
    return claims;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int z = inf.readInt();
    cases.reserve(z);
    for (int tc = 0; tc < z; ++tc) {
        int n = inf.readInt();
        int m = inf.readInt();
        vector<int> forecast(m);
        for (int i = 0; i < m; ++i) {
            forecast[i] = inf.readInt();
        }
        cases.push_back({n, forecast});
    }

    vector<Claim> jury = readAllClaims(ans);
    vector<Claim> participant = readAllClaims(ouf);

    for (int i = 0; i < z; ++i) {
        if (jury[i].possible && !participant[i].possible) {
            quitf(_wa, "case %d is possible according to jury, but participant printed NO", i + 1);
        }
        if (!jury[i].possible && participant[i].possible) {
            quitf(_fail, "case %d has valid participant YES while jury printed NO", i + 1);
        }
    }

    quitf(_ok, "all %d case(s) match the jury feasibility claim", z);
}
