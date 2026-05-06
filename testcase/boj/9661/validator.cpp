#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of stones, must satisfy 1 ≤ N ≤ 10^12
    long long N = inf.readLong(1LL, 1000000000000LL, "N");
    inf.readEoln();

    // No more data
    inf.readEof();
    return 0;
}
