#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 499999, "N");
    inf.readEoln();
    ensuref(n % 2 == 1, "N must be odd, got %d", n);

    vector<int> a = inf.readInts(n, 1, 1000000000, "A_i");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(a[i]).second, "duplicate A_i at index %d: %d", i + 1, a[i]);
    }

    inf.readEof();
}
