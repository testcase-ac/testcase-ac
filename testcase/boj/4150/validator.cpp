#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read a single positive integer n
    // No explicit upper bound given in statement, so we allow up to 1e18
    long long n = inf.readLong(1LL, (long long)1e18, "n");
    inf.readEoln();

    // No further global constraints (answer always exists for n>=1)

    inf.readEof();
    return 0;
}
