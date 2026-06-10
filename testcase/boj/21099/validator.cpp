#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 100000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 0, 100000, "A_i");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(a[i]).second,
                "A_i values must be distinct, duplicate at index %d: %d",
                i + 1,
                a[i]);
    }

    inf.readEof();
}
