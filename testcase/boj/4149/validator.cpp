#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the integer N: 1 < N < 2^62
    long long N = inf.readLong(2LL, (1LL << 62) - 1, "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
