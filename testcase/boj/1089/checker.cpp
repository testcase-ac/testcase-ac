#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    if (ans.seekEof()) quitf(_fail, "Jury output is empty");
    if (ouf.seekEof()) quitf(_wa,   "Participant output is empty");

    const double EPS = 1e-5;

    double j = ans.readDouble();
    double p = ouf.readDouble();

    if (!ans.seekEof()) quitf(_fail, "Jury output has extra tokens");
    if (!ouf.seekEof()) quitf(_pe,   "Extra tokens in participant output");

    if (!std::isfinite(p)) quitf(_wa, "Participant output is not finite (nan/inf)");
    if (!std::isfinite(j)) quitf(_fail, "Jury output is not finite (nan/inf)");

    if (fabs(j + 1.0) <= 5e-13) {
        if (fabs(p + 1.0) <= 1e-7) {
            quitf(_ok, "OK: both are -1");
        } else {
            quitf(_wa, "Expected -1, found %.15g", p);
        }
    }

    double diff = fabs(p - j);
    double tol = EPS * max(1.0, fabs(j)); 

    if (diff <= tol) {
        quitf(_ok, "OK: participant=%.15g jury=%.15g diff=%.3g tol=%.3g", p, j, diff, tol);
    } else {
        quitf(_wa, "Wrong: participant=%.15g jury=%.15g diff=%.3g tol=%.3g", p, j, diff, tol);
    }
}
