#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read k: must be a natural number within [1, 10^18]
    long long k = inf.readLong(1LL, 1000000000000000000LL, "k");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
