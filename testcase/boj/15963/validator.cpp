#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Battery types N and M: integers with up to 10 digits.
    // We interpret this as values in the range [-9999999999, 9999999999].
    long long N = inf.readLong(-9999999999LL, 9999999999LL, "N");
    inf.readSpace();
    long long M = inf.readLong(-9999999999LL, 9999999999LL, "M");
    inf.readEoln();

    // No further global constraints to check: just two integers.
    inf.readEof();
    return 0;
}
