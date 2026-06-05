#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    inf.readInt(2, 100000, "k");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    set<long long> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(a[i]).second, "a_i values must be distinct, duplicate value %lld at index %d", a[i], i + 1);
    }

    inf.readEof();
}
