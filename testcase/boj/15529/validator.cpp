#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 10000, "a_i");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(a[i]).second, "a_i values must be distinct, duplicate %d at index %d", a[i], i + 1);
    }

    inf.readEof();
}
