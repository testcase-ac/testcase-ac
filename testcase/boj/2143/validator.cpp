#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read target sum T
    long long T = inf.readLong(-1000000000LL, 1000000000LL, "T");
    inf.readEoln();

    // Read array A
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();
    inf.readLongs(n, -1000000LL, 1000000LL, "A");
    inf.readEoln();

    // Read array B
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();
    inf.readLongs(m, -1000000LL, 1000000LL, "B");
    inf.readEoln();

    // No additional global constraints to check
    inf.readEof();
    return 0;
}
