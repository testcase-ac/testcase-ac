#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 1 ≤ N ≤ 10^9
    long long N = inf.readLong(1LL, 1000000000LL, "N");
    // After N, there must be exactly one newline and nothing else on the line
    inf.readEoln();
    // No extra data after this
    inf.readEof();

    return 0;
}
