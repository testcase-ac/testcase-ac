#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

const double EPS = 1e-6;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read team names in input order
    vector<string> teams(4);
    for (int i = 0; i < 4; i++) {
        teams[i] = inf.readToken();
    }

    // Read and compare the 4 probabilities
    for (int i = 0; i < 4; i++) {
        double jans = ans.readDouble();
        double pans = ouf.readDouble();
        if (!doubleCompare(jans, pans, EPS)) {
            quitf(_wa,
                  "team %s: expected '%.10f', found '%.10f', error = '%.10f'",
                  teams[i].c_str(),
                  jans, pans,
                  doubleDelta(jans, pans));
        }
    }

    // Check for any extra output from contestant
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output");
    }

    quitf(_ok, "correct");
    return 0;
}
