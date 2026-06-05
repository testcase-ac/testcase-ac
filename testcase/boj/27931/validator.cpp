#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "n");
    inf.readEoln();

    vector<long long> x = inf.readLongs(n, -1000000000LL, 1000000000LL, "x_i");
    inf.readEoln();

    set<long long> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(x[i]).second,
                "duplicate coordinate at index %d: %lld", i + 1, x[i]);
    }

    inf.readEof();
}
