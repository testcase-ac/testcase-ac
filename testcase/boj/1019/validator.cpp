#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: a natural number between 1 and 1e9 inclusive.
    long long N = inf.readLong(1LL, 1000000000LL, "N");
    inf.readEoln();

    // No more input is allowed.
    inf.readEof();
    return 0;
}
