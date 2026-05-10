#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: N and L on the first line
    long long N = inf.readLong(1LL, 10000000LL, "N");
    inf.readSpace();
    long long L = inf.readLong(1LL, 1000000000LL, "L");
    inf.readEoln();

    // No further constraints to check beyond ranges and formatting.

    inf.readEof();
}
