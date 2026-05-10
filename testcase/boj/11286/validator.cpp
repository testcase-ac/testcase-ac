#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of operations
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Each of the next N lines contains one integer x
    // x must satisfy -2^31 < x < 2^31, i.e. x in [-2^31+1, 2^31-1]
    const long long MIN_X = -2147483647LL;
    const long long MAX_X =  2147483647LL;
    for (int i = 0; i < N; i++) {
        long long x = inf.readLong(MIN_X, MAX_X, "x");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
