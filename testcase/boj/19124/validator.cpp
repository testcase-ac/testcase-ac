#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: 1 <= n <= 1e18
    long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
    inf.readSpace();
    // Read k: 0 <= k <= n
    long long k = inf.readLong(0LL, n, "k");
    inf.readEoln();

    // exactly one test case, ensure no extra data
    inf.readEof();
    return 0;
}
