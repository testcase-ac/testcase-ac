#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int n;
map<string, pair<double, double>> runner; // name -> (a_i for leg1, b_i for other legs)

// readAns reads from stream (ans or ouf), checks validity, computes and returns the total time.
double readAns(InStream &stream) {
    // Read the time printed by participant/jury and ignore it for correctness.
    // We'll compute the real time from the names they output.
    double printedTime = stream.readDouble();
    (void)printedTime; // unused

    vector<string> names;
    names.reserve(4);
    for (int i = 0; i < 4; i++) {
        string s = stream.readToken();
        names.push_back(s);
    }

    // Check that all names exist and are distinct
    set<string> used;
    for (int i = 0; i < 4; i++) {
        const string &s = names[i];
        if (runner.find(s) == runner.end()) {
            stream.quitf(_wa, "unknown runner '%s' on leg %d", s.c_str(), i+1);
        }
        if (!used.insert(s).second) {
            stream.quitf(_wa, "runner '%s' used more than once", s.c_str());
        }
    }

    // Compute total time: a of leg1 + b of legs 2,3,4
    double total = 0.0;
    total += runner[names[0]].first;
    for (int i = 1; i < 4; i++) {
        total += runner[names[i]].second;
    }
    return total;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    n = inf.readInt();
    for (int i = 0; i < n; i++) {
        string name = inf.readToken();
        double a = inf.readDouble();
        double b = inf.readDouble();
        runner[name] = {a, b};
    }

    double jans = readAns(ans);
    double pans = readAns(ouf);

    const double EPS = 1e-6;
    if (jans > pans + EPS) {
        quitf(_wa, "jury has a better team: jury = %.6f, participant = %.6f", jans, pans);
    } else if (jans + EPS < pans) {
        quitf(_fail, "participant has a better team: jury = %.6f, participant = %.6f", jans, pans);
    } else {
        quitf(_ok, "best time = %.6f", pans);
    }
}
