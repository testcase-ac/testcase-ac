#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 500000, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000LL, "K");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 1000000000, "A_i");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(a[i]).second,
                "A_i values must be distinct, duplicate value %d at index %d",
                a[i], i + 1);
    }

    inf.readEof();
}
