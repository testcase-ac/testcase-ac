#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int v = inf.readInt(2, 1000, "V");
    inf.readSpace();
    int e = inf.readInt(1, v * (v - 1) / 2, "E");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 0; i < e; ++i) {
        int a = inf.readInt(1, v, "a");
        inf.readSpace();
        int b = inf.readInt(1, v, "b");
        inf.readEoln();

        ensuref(a != b, "edge %d is a loop: %d %d", i + 1, a, b);
        pair<int, int> edge = minmax(a, b);
        ensuref(edges.insert(edge).second,
                "edge %d is duplicated: %d %d", i + 1, a, b);
    }

    inf.readEof();
}
