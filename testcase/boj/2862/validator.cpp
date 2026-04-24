#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of coins
    long long N = inf.readLong(2LL, 1000000000000000LL, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
