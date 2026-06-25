#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

static void ensureDistinct(const vector<long long>& values, const char* name) {
    set<long long> seen;
    for (int i = 0; i < int(values.size()); ++i) {
        ensuref(seen.insert(values[i]).second,
                "%s values must be distinct, duplicate at index %d: %lld",
                name, i + 1, values[i]);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 10000, "N");
    inf.readSpace();
    inf.readInt(1, n, "Q");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "A_i");
    inf.readEoln();
    vector<long long> b = inf.readLongs(n, 1LL, 1000000000LL, "B_i");
    inf.readEoln();

    ensureDistinct(a, "A");
    ensureDistinct(b, "B");

    inf.readEof();
}
