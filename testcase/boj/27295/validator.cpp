#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and b
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    long long b = inf.readLong(-1000000000LL, 1000000000LL, "b");
    inf.readEoln();

    // Read n points (x_i, y_i)
    for (int i = 0; i < n; i++) {
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        long long y = inf.readLong(-1000000000LL, 1000000000LL, "y_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
