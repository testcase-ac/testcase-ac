#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read x and y: natural numbers (>=1) and <= 1e9
    long long x = inf.readLong(1LL, 1000000000LL, "x");
    // There must be at least one whitespace between x and y
    inf.readSpace();
    long long y = inf.readLong(1LL, 1000000000LL, "y");
    // End of line after y
    inf.readEoln();
    // No extra characters after the single line
    inf.readEof();
    return 0;
}
