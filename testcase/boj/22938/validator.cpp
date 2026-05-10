#include "testlib.h"
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First circle: X1 Y1 R1
    long long x1 = inf.readLong(-1000000000LL, 1000000000LL, "X1");
    inf.readSpace();
    long long y1 = inf.readLong(-1000000000LL, 1000000000LL, "Y1");
    inf.readSpace();
    long long r1 = inf.readLong(1LL, 1000000000LL, "R1");
    inf.readEoln();

    // Second circle: X2 Y2 R2
    long long x2 = inf.readLong(-1000000000LL, 1000000000LL, "X2");
    inf.readSpace();
    long long y2 = inf.readLong(-1000000000LL, 1000000000LL, "Y2");
    inf.readSpace();
    long long r2 = inf.readLong(1LL, 1000000000LL, "R2");
    inf.readEoln();

    // No extra lines allowed
    inf.readEof();

    return 0;
}
