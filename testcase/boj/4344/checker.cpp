#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static const double EPS = 1e-3;

// Reads one percentage token like "40.000%" from the given stream,
// parses it into a double, and on format error quits with _wa for ouf,
// or _fail for ans.
double readPercent(InStream &stream) {
    string s = stream.readToken();
    if (s.empty() || s.back() != '%') {
        // missing '%' sign
        stream.quitf((&stream == &ouf ? _wa : _fail),
                     "invalid format: missing '%%' in \"%s\"", s.c_str());
    }
    string num = s.substr(0, s.size() - 1);
    char *endp = nullptr;
    double val = strtod(num.c_str(), &endp);
    if (endp != num.c_str() + num.size()) {
        // not a valid number
        stream.quitf((&stream == &ouf ? _wa : _fail),
                     "invalid number in \"%s\"", s.c_str());
    }
    return val;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read number of test cases
    int C = inf.readInt();
    if (C < 0)  // sanity
        quitf(_fail, "invalid number of cases: %d", C);

    // Read jury output
    vector<double> jury(C);
    for (int i = 0; i < C; i++) {
        jury[i] = readPercent(ans);
    }
    // Read participant output
    vector<double> part(C);
    for (int i = 0; i < C; i++) {
        part[i] = readPercent(ouf);
    }

    // Compare each case
    for (int i = 0; i < C; i++) {
        double j = jury[i], p = part[i];
        double ad = fabs(j - p);
        double rd = ad / max(fabs(j), 1.0);
        if (ad > EPS && rd > EPS) {
            // mismatch beyond allowed absolute/relative error
            char bufJ[64], bufP[64];
            sprintf(bufJ, "%.3f%%", j);
            sprintf(bufP, "%.3f%%", p);
            quitf(_wa,
                  "Case #%d: expected %s, found %s",
                  i + 1, bufJ, bufP);
        }
    }

    // All good
    quitf(_ok, "All %d cases passed", C);
    return 0;
}
