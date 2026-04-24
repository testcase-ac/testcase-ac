#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and D
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long D = inf.readLong(0LL, 1000000000LL, "D");
    inf.readEoln();

    // Read 2N pies: first N are Bessie's, next N are Elsie's
    for (int i = 0; i < 2 * N; i++) {
        // tastiness according to Bessie
        inf.readLong(0LL, 1000000000LL, "b_i");
        inf.readSpace();
        // tastiness according to Elsie
        inf.readLong(0LL, 1000000000LL, "e_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
