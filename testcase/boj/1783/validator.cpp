#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M: natural numbers (>=1) and <= 2e9
    long long N = inf.readLong(1LL, 2000000000LL, "N");
    inf.readSpace();
    long long M = inf.readLong(1LL, 2000000000LL, "M");
    inf.readEoln();

    inf.readEof();
    return 0;
}
