#include "testlib.h"
#include <string>

using namespace std;

const double EPS = 1e-4;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the expected answers (jury) and contestant answers
    double ja, jb, jc;
    double pa, pb, pc;

    ja = ans.readDouble();
    jb = ans.readDouble();
    jc = ans.readDouble();

    pa = ouf.readDouble();
    pb = ouf.readDouble();
    pc = ouf.readDouble();

    // Make sure there is no extra output from the contestant
    ouf.readEof();

    // Compare each of the three numbers
    if (!doubleCompare(ja, pa, EPS)) {
        quitf(_wa, "First number differs - expected: '%.6f', found: '%.6f', error = '%.6f'",
              ja, pa, doubleDelta(ja, pa));
    }
    if (!doubleCompare(jb, pb, EPS)) {
        quitf(_wa, "Second number differs - expected: '%.6f', found: '%.6f', error = '%.6f'",
              jb, pb, doubleDelta(jb, pb));
    }
    if (!doubleCompare(jc, pc, EPS)) {
        quitf(_wa, "Third number differs - expected: '%.6f', found: '%.6f', error = '%.6f'",
              jc, pc, doubleDelta(jc, pc));
    }

    quitf(_ok, "All values are correct");
    return 0;
}
