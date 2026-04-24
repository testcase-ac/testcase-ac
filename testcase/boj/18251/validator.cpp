#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of nodes
    int N = inf.readInt(1, 262143, "N");
    inf.readEoln();

    // N must be of the form 2^k - 1
    // i.e., N+1 is a power of two
    ensuref(((long long)N + 1 & (long long)N) == 0,
            "N+1 must be a power of two, but got N=%d", N);

    // Read N weights
    vector<long long> W = inf.readLongs(N, -1000000000LL, 1000000000LL, "W_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
