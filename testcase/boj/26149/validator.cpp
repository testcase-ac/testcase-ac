#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000LL, "m");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 0LL, 1000000000LL, "a_i");
    inf.readEoln();

    vector<long long> b = inf.readLongs(n, 0LL, 1000000000LL, "b_i");
    inf.readEoln();

    long long sum_a = accumulate(a.begin(), a.end(), 0LL);
    long long sum_b = accumulate(b.begin(), b.end(), 0LL);
    ensuref(sum_a == m, "sum of A must be M: expected %lld, found %lld", m, sum_a);
    ensuref(sum_b == m, "sum of B must be M: expected %lld, found %lld", m, sum_b);

    inf.readEof();
}
