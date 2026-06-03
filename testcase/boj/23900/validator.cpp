#include "testlib.h"

#include <unordered_set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 500000, "N");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "A_i");
    inf.readEoln();

    vector<long long> b = inf.readLongs(n, 1LL, 1000000000LL, "B_i");
    inf.readEoln();

    unordered_set<long long> seen;
    seen.reserve(static_cast<size_t>(n) * 2);
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(a[i]).second, "A_i values must be distinct; duplicate %lld at index %d", a[i], i + 1);
    }

    seen.clear();
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(b[i]).second, "B_i values must be distinct; duplicate %lld at index %d", b[i], i + 1);
    }

    inf.readEof();
}
