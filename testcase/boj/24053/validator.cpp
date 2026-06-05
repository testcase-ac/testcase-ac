#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 10000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000000, "a_i");
    inf.readEoln();

    set<int> seenA;
    for (int i = 0; i < n; ++i) {
        ensuref(seenA.insert(a[i]).second, "duplicate A value at index %d: %d", i + 1, a[i]);
    }

    inf.readInts(n, 1, 1000000000, "b_i");
    inf.readEoln();

    inf.readEof();
}
