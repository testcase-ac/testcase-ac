#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of phones
    int n = inf.readInt(2, 200000, "n");
    inf.readEoln();

    // Read each phone's (x, y, z)
    for (int i = 1; i <= n; i++) {
        long long x = inf.readLong(1LL, 1000000000LL, "x_i");
        inf.readSpace();
        long long y = inf.readLong(1LL, 1000000000LL, "y_i");
        inf.readSpace();
        long long z = inf.readLong(1LL, 1000000000LL, "z_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
