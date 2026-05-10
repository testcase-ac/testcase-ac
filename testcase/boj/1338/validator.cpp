#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: two integers a, b (range endpoints)
    int a = inf.readInt(-2147483648, 2147483647, "a");
    inf.readSpace();
    int b = inf.readInt(-2147483648, 2147483647, "b");
    inf.readEoln();

    // Read second line: x (divisor), y (remainder)
    int x = inf.readInt(-2147483648, 2147483647, "x");
    inf.readSpace();
    int y = inf.readInt(-2147483648, 2147483647, "y");
    inf.readEoln();

    // |x| must not be zero for modulus to make sense
    ensuref(x != 0, "x (divisor) must not be zero");

    // y must be in [0, |x| - 1]
    int abs_x = x > 0 ? x : -x;
    ensuref(y >= 0 && y < abs_x, "y (remainder) must satisfy 0 <= y < |x|, but got y=%d, x=%d", y, x);

    inf.readEof();
}
