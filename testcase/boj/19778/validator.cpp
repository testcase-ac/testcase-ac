#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, n, "m");
    inf.readEoln();

    long long l1 = inf.readLong(1LL, 1000000000LL, "l1");
    inf.readSpace();
    long long r1 = inf.readLong(1LL, 1000000000LL, "r1");
    inf.readEoln();
    ensuref(l1 <= r1, "l1 must not exceed r1: %lld > %lld", l1, r1);

    long long l2 = inf.readLong(1LL, 1000000000LL, "l2");
    inf.readSpace();
    long long r2 = inf.readLong(1LL, 1000000000LL, "r2");
    inf.readEoln();
    ensuref(l2 <= r2, "l2 must not exceed r2: %lld > %lld", l2, r2);

    vector<long long> heights = inf.readLongs(n, 1LL, 1000000000LL, "h_i");
    inf.readEoln();

    inf.readEof();
}
