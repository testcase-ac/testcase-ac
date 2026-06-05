#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 1, 100000, "a");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(a[i]).second, "a[%d] is duplicated: %d", i + 1, a[i]);
    }

    inf.readEof();
}
