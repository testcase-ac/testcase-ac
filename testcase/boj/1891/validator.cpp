#include "testlib.h"
#include <string>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: d and quadrant number
    int d = inf.readInt(1, 50, "d");
    inf.readSpace();

    // Read the quadrant number as a string of length d, each digit in [1,4]
    string quad = inf.readToken("[1-4]{1,50}", "quadrant_number");
    ensuref((int)quad.size() == d, "Quadrant number length (%d) does not match d (%d)", (int)quad.size(), d);

    inf.readEoln();

    // Second line: x and y
    // |x|, |y| <= 2^50
    // 2^50 = 1125899906842624
    long long minXY = -1125899906842624LL;
    long long maxXY = 1125899906842624LL;
    long long x = inf.readLong(minXY, maxXY, "x");
    inf.readSpace();
    long long y = inf.readLong(minXY, maxXY, "y");
    inf.readEoln();

    inf.readEof();
}
