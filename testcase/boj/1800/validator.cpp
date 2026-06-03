#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int p = inf.readInt(1, 10000, "P");
    inf.readSpace();
    int k = inf.readInt(0, n - 1, "K");
    inf.readEoln();

    set<pair<int, int>> seen;
    for (int i = 1; i <= p; ++i) {
        int a = inf.readInt(1, n, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "B_i");
        inf.readSpace();
        int l = inf.readInt(1, 1000000, "L_i");
        inf.readEoln();

        ensuref(a != b, "edge %d has identical endpoints: %d", i, a);
        pair<int, int> edge = minmax(a, b);
        ensuref(seen.insert(edge).second,
                "duplicate unordered edge at index %d: (%d, %d), length %d",
                i, a, b, l);
    }

    inf.readEof();
}
