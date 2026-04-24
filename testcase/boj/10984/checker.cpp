#include "testlib.h"
#include <cmath>
#include <string>
using namespace std;

const double EPS = 1e-1;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt();
    for (int i = 1; i <= T; i++) {
        // Read jury's answer
        int jc = ans.readInt();
        double jg = ans.readDouble();
        // Read participant's answer
        int pc = ouf.readInt();
        double pg = ouf.readDouble();

        if (pc != jc) {
            quitf(_wa, "semester %d: total credits differ, expected %d, found %d",
                  i, jc, pc);
        }
        double diff = fabs(jg - pg);
        if (diff > EPS) {
            quitf(_wa,
                  "semester %d: GPA differ, expected '%.7f', found '%.7f', "
                  "absolute error = '%.7f' (> %.1f)",
                  i, jg, pg, diff, EPS);
        }
    }

    // Check for extra output
    if (!ouf.seekEof()) {
        quitf(_wa, "extra tokens in participant output after %d semesters", T);
    }

    quitf(_ok, "All %d semesters match within absolute error %.1f", T, EPS);
    return 0;
}
