#include "testlib.h"
#include <cmath>
using namespace std;

const double EPS = 1e-6;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int caseNum = 0;
    // Compare each answer (jury vs participant) line by line
    while (!ans.seekEof()) {
        caseNum++;
        double ja = ans.readDouble();
        double pa = ouf.readDouble();

        if (!doubleCompare(ja, pa, EPS)) {
            quitf(_wa,
                  "Case #%d: expected '%.10f', found '%.10f', diff=%.10f",
                  caseNum, ja, pa, fabs(ja - pa));
        }
    }
    // Check for extra output from the participant
    if (!ouf.seekEof()) {
        quitf(_wa, "Extra output after reading %d cases", caseNum);
    }
    quitf(_ok, "All %d cases matched (EPS=%.1e)", caseNum, EPS);
}
