#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input data
    long long K = inf.readLong();     // total amount to distribute
    int N        = inf.readInt();     // number of projects

    // Read contestant's output: N numbers
    vector<long long> a;
    a.reserve(N);
    for (int i = 0; i < N; i++) {
        if (ouf.eof())
            ouf.quitf(_wa, "too few numbers: expected %d, found %d", N, i);
        a.push_back(ouf.readLong());
    }
    // Check for extra data
    if (!ouf.seekEof())
        ouf.quitf(_wa, "extra data after reading %d numbers", N);

    // Validate the distribution
    long long sum = 0;
    set<long long> seen;
    for (int i = 0; i < N; i++) {
        long long x = a[i];
        if (x < 1)
            ouf.quitf(_wa, "invalid amount on line %d: %lld (should be >= 1)", i+1, x);
        if (seen.count(x))
            ouf.quitf(_wa, "amount %lld occurs more than once", x);
        seen.insert(x);
        sum += x;
    }
    if (sum != K)
        ouf.quitf(_wa, "sum of amounts is %lld but expected %lld", sum, K);

    // All checks passed
    quitf(_ok, "valid distribution");
}
