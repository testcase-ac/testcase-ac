#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 10000, "n");
    inf.readSpace();
    int q = inf.readInt(1, n, "q");
    inf.readSpace();
    int k = inf.readInt(1, 100000000, "k");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000000, "a_i");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(a[i]).second, "duplicate A_i at index %d: %d", i + 1, a[i]);
    }

    inf.readEof();
}
