#include "testlib.h"

using namespace std;

const double EPS = 1e-6;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int cnt = 0;
    double jv = 0.0, pv = 0.0;

    while (!ans.seekEof()) {
        cnt++;
        jv = ans.readDouble();
        pv = ouf.readDouble();
        if (!doubleCompare(jv, pv, EPS)) {
            quitf(_wa,
                  "%d%s numbers differ - expected: '%.10f', found: '%.10f', error = '%.10f'",
                  cnt, englishEnding(cnt).c_str(), jv, pv, doubleDelta(jv, pv));
        }
    }

    if (cnt == 0) {
        quitf(_wa, "no output");
    } else if (cnt == 1) {
        quitf(_ok, "found '%.10f', expected '%.10f', error '%.10f'",
              pv, jv, doubleDelta(jv, pv));
    } else {
        quitf(_ok, "%d numbers", cnt);
    }
}
