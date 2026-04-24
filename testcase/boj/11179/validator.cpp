#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer N
    long long N = inf.readLong(1LL, 1000000000LL, "N");
    // After N, there must be exactly one end-of-line
    inf.readEoln();
    // And then immediately EOF
    inf.readEof();

    return 0;
}
