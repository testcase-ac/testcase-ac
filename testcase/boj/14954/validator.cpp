#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer n, must be in [1, 1e9]
    long long n = inf.readLong(1LL, 1000000000LL, "n");
    inf.readEoln();

    // No more data
    inf.readEof();
    return 0;
}
