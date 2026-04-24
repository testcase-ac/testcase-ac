#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read fixed cost A, variable cost B, price C.
    // All are natural numbers (>=1) and <= 2,100,000,000.
    long long A = inf.readLong(1LL, 2100000000LL, "A");
    inf.readSpace();
    long long B = inf.readLong(1LL, 2100000000LL, "B");
    inf.readSpace();
    long long C = inf.readLong(1LL, 2100000000LL, "C");
    inf.readEoln();

    // No further global constraints to check.
    inf.readEof();
    return 0;
}
