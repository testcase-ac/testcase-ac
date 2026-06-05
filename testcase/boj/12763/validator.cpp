#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readEoln();

    int t = inf.readInt(1, 10000, "T");
    inf.readSpace();
    int m = inf.readInt(0, 10000, "M");
    inf.readEoln();

    int l = inf.readInt(1, 10000, "L");
    inf.readEoln();

    set<pair<int, int>> roads;
    for (int i = 1; i <= l; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        int time = inf.readInt(1, 10000, "time");
        inf.readSpace();
        int cost = inf.readInt(1, 10000, "cost");
        inf.readEoln();

        ensuref(a != b, "road %d has identical endpoints: %d", i, a);
        pair<int, int> road = minmax(a, b);
        ensuref(roads.insert(road).second,
                "duplicate undirected road at index %d: %d %d", i, a, b);
    }

    inf.readEof();
}
