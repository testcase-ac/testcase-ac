#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: a natural number (>=1) and <= 10^18
    long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
    inf.readEoln();
    inf.readEof();
    return 0;
}
