#include "testlib.h"
#include <string>
#include <cstdlib>
using namespace std;

const double EPS = 1e-6;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read jury answer
    string js = ans.readToken();
    bool jImp = false;
    double jF = 0;
    if (js == "impossible") {
        jImp = true;
    } else {
        // parse as double
        jF = atof(js.c_str());
    }
    // Read participant answer
    if (ouf.eof())
        quitf(_pe, "no output");
    string ps = ouf.readToken();
    bool pImp = false;
    double pF = 0;
    if (ps == "impossible") {
        pImp = true;
    } else {
        pF = atof(ps.c_str());
    }
    // Check for extra tokens
    ouf.skipBlanks();
    if (!ouf.eof())
        quitf(_pe, "extra tokens after answer");

    // Compare
    if (jImp) {
        // Jury says impossible
        if (pImp)
            quitf(_ok, "impossible");
        else
            quitf(_wa, "expected impossible, found '%.7f'", pF);
    } else {
        // Jury has a number
        if (pImp)
            quitf(_wa, "found impossible, expected '%.7f'", jF);
        if (!doubleCompare(jF, pF, EPS)) {
            quitf(_wa,
                  "expected '%.7f', found '%.7f', error = '%.7f'",
                  jF, pF, doubleDelta(jF, pF));
        } else {
            quitf(_ok, "f = '%.7f'", pF);
        }
    }
    return 0;
}
