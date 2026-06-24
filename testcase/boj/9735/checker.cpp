#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

static const double EPS = 1e-4;

struct CaseAnswer {
    vector<double> roots;
};

static CaseAnswer readCaseAnswer(InStream& stream, int tc) {
    vector<double> roots;
    string line = stream.readLine();
    stringstream parser(line);

    while (true) {
        double root;
        if (!(parser >> root)) {
            break;
        }
        if (!isfinite(root)) {
            stream.quitf(_wa, "case %d root %d is not finite", tc,
                         (int)roots.size() + 1);
        }
        roots.push_back(root);
    }

    parser >> ws;
    if (!parser.eof()) {
        stream.quitf(_wa, "case %d contains a malformed root token", tc);
    }
    if (roots.empty()) {
        stream.quitf(_wa, "case %d has no roots", tc);
    }

    for (int i = 0; i < (int)roots.size(); ++i) {
        if (roots[i] < -1000000.0001 || roots[i] > 1000000.0001) {
            stream.quitf(_wa, "case %d root %d is outside allowed range: %.10f",
                         tc, i + 1, roots[i]);
        }
        if (i > 0 && roots[i - 1] >= roots[i]) {
            stream.quitf(_wa,
                         "case %d roots are not strictly increasing at positions %d and %d: %.10f %.10f",
                         tc, i, i + 1, roots[i - 1], roots[i]);
        }
    }

    return {roots};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    for (int tc = 1; tc <= n; ++tc) {
        inf.readLong();
        inf.readLong();
        inf.readLong();
        inf.readLong();

        CaseAnswer jury = readCaseAnswer(ans, tc);
        CaseAnswer participant = readCaseAnswer(ouf, tc);

        if (participant.roots.size() != jury.roots.size()) {
            quitf(_wa, "case %d expected %d roots, found %d roots", tc,
                  (int)jury.roots.size(), (int)participant.roots.size());
        }

        for (int i = 0; i < (int)jury.roots.size(); ++i) {
            if (!doubleCompare(jury.roots[i], participant.roots[i], EPS)) {
                quitf(_wa,
                      "case %d root %d differs: expected %.10f, found %.10f, error %.10f",
                      tc, i + 1, jury.roots[i], participant.roots[i],
                      doubleDelta(jury.roots[i], participant.roots[i]));
            }
        }
    }

    if (!ans.seekEof()) {
        quitf(_fail, "extra output after jury answer");
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after participant answer");
    }

    quitf(_ok, "all %d cases are within tolerance", n);
}
