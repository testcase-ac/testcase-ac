#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 10000, "n");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    set<long long> seenA;
    for (int i = 0; i < n; ++i) {
        ensuref(seenA.insert(a[i]).second,
                "a_i values must be distinct, duplicate at index %d: %lld",
                i + 1, a[i]);
    }

    // CHECK: The statement bounds B_i but does not require B to be distinct or a permutation of A.
    inf.readLongs(n, 1LL, 1000000000LL, "b_i");
    inf.readEoln();

    inf.readEof();
}
