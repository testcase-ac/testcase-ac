#include "testlib.h"

#include <cmath>
#include <string>
#include <vector>

using namespace std;

const double EPS = 1e-6;

struct Claim {
    bool impossible;
    double area;
};

Claim readClaim(InStream& stream, TResult invalidStatus, int caseNo) {
    string token = stream.readWord();
    if (token == "IMPOSSIBLE") {
        return {true, 0.0};
    }

    char* end = nullptr;
    double area = strtod(token.c_str(), &end);
    if (end == token.c_str() || *end != '\0') {
        stream.quitf(invalidStatus,
                     "case %d: expected IMPOSSIBLE or an area, found '%s'",
                     caseNo,
                     token.c_str());
    }
    if (!isfinite(area)) {
        stream.quitf(invalidStatus, "case %d: area is not finite", caseNo);
    }
    if (area < 0.0) {
        stream.quitf(invalidStatus, "case %d: area %.17g is negative", caseNo, area);
    }

    return {false, area};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int k = inf.readInt();
    vector<Claim> jury(k);
    vector<Claim> participant(k);

    for (int tc = 1; tc <= k; ++tc) {
        jury[tc - 1] = readClaim(ans, _fail, tc);
    }
    if (!ans.seekEof()) {
        quitf(_fail, "extra output after %d jury answers", k);
    }

    for (int tc = 1; tc <= k; ++tc) {
        participant[tc - 1] = readClaim(ouf, _wa, tc);
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after %d participant answers", k);
    }

    for (int tc = 1; tc <= k; ++tc) {
        const Claim& expected = jury[tc - 1];
        const Claim& found = participant[tc - 1];

        if (expected.impossible) {
            if (!found.impossible) {
                quitf(_wa,
                      "case %d: expected IMPOSSIBLE, found area %.17g",
                      tc,
                      found.area);
            }
            continue;
        }

        if (found.impossible) {
            quitf(_wa, "case %d: expected area %.17g, found IMPOSSIBLE", tc, expected.area);
        }
        double error = fabs(expected.area - found.area);
        if (error > EPS) {
            quitf(_wa,
                  "case %d: expected %.17g, found %.17g, error %.17g",
                  tc,
                  expected.area,
                  found.area,
                  error);
        }
    }

    quitf(_ok, "%d answers are valid", k);
}
