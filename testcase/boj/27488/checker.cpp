#include "testlib.h"
#include <string>
#include <cmath>
using namespace std;

// Compute sum of decimal digits of non-negative integer x.
int sumDigits(int x) {
    int s = 0;
    while (x > 0) {
        s += x % 10;
        x /= 10;
    }
    return s;
}

// Read one answer (pair x,y) for test number testNum from stream,
// verify 0 <= x,y <= n, x+y == n, and |sumDigits(x)-sumDigits(y)| <= 1.
// On error, quits with _wa if stream==ouf or with _fail if stream==ans.
void readAnswerCase(InStream& stream, int testNum, int n) {
    int x = stream.readInt(0, n,
        format("x (test #%d)", testNum).c_str());
    int y = stream.readInt(0, n,
        format("y (test #%d)", testNum).c_str());
    if (x + y != n) {
        stream.quitf(_wa,
            "test #%d: x + y = %d, expected %d", 
            testNum, x + y, n);
    }
    int sx = sumDigits(x);
    int sy = sumDigits(y);
    int diff = abs(sx - sy);
    if (diff > 1) {
        stream.quitf(_wa,
            "test #%d: |sumDigits(x)-sumDigits(y)| = %d > 1 (x=%d, y=%d, sumDigits: %d, %d)",
            testNum, diff, x, y, sx, sy);
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int t = inf.readInt();  // number of test cases
    for (int i = 1; i <= t; i++) {
        int n = inf.readInt();
        // First read jury's answer and verify its correctness.
        readAnswerCase(ans, i, n);
        // Then read participant's answer and verify.
        readAnswerCase(ouf, i, n);
    }
    // Ensure there's no extra output from participant.
    ouf.readEof();
    quitf(_ok, "All tests passed");
}
