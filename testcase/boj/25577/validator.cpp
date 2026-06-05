#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 100000, "n");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, -1000000000LL, 1000000000LL, "a_i");
    inf.readEoln();
    inf.readEof();

    set<long long> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(a[i]).second, "duplicate array value at index %d: %lld", i + 1, a[i]);
    }
}
