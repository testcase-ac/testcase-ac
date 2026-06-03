#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(2LL, 1000000000LL, "n");
    inf.readSpace();
    int k = inf.readInt(1, 100, "k");
    inf.readEoln();

    ensuref(k < n, "k must be less than n: k=%d, n=%lld", k, n);

    vector<long long> a = inf.readLongs(k, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    long long p = inf.readLong(1LL, 1000000007LL, "P");
    inf.readEoln();

    inf.readEof();
}
