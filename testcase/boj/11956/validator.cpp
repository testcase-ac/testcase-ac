#include "testlib.h"
using namespace std;

static const long long A_UP = 1000000000000000000LL - 1; // a_i < 1e18
static const long long LR_UP = 1000000000000000000LL;    // l_i, r_i <= 1e18

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // Read initial sequence a_1 ... a_K, each 0 <= a_i < 1e18
    inf.readLongs(K, 0LL, A_UP, "a_i");
    inf.readEoln();

    // Read Q
    int Q = inf.readInt(1, 1000000, "Q");
    inf.readEoln();

    // Read Q queries
    for (int i = 0; i < Q; i++) {
        long long l = inf.readLong(1LL, LR_UP, "l_i");
        inf.readSpace();
        long long r = inf.readLong(1LL, LR_UP, "r_i");
        inf.readEoln();
        ensuref(l <= r,
                "Query %d is invalid: l_i (%lld) > r_i (%lld)", 
                i+1, l, r);
    }

    inf.readEof();
    return 0;
}
