#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K and N
    int K = inf.readInt(1, 50, "K");
    inf.readSpace();
    // N must be at least K and at most 50
    int N = inf.readInt(K, 50, "N");
    inf.readEoln();

    // Read the K numbers, one per line
    for (int i = 0; i < K; i++) {
        long long x = inf.readLong(1LL, 1000000000LL, "a_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
