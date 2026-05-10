#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read D, P, Q: natural numbers up to 1e9
    long long D = inf.readLong(1LL, 1000000000LL, "D");
    inf.readSpace();
    long long P = inf.readLong(1LL, 1000000000LL, "P");
    inf.readSpace();
    long long Q = inf.readLong(1LL, 1000000000LL, "Q");
    inf.readEoln();

    // No further constraints on P and Q (they can be equal or in any order)

    inf.readEof();
    return 0;
}
