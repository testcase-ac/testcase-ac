#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    vector<int> positions = inf.readInts(n, 0, 1000000000, "position");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(positions[i]).second,
                "duplicate haybale position at index %d: %d",
                i + 1,
                positions[i]);
    }

    for (int i = 0; i < q; ++i) {
        int a = inf.readInt(0, 1000000000, "a");
        inf.readSpace();
        int b = inf.readInt(a, 1000000000, "b");
        inf.readEoln();
    }

    inf.readEof();
}
