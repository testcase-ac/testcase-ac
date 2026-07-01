#include "testlib.h"

#include <vector>

using namespace std;

bool isAncestor(int ancestor, int vertex) {
    if (ancestor == 0) {
        return true;
    }

    int width = 0;
    int x = ancestor;
    while (x > 0) {
        ++width;
        x >>= 1;
    }

    int mask = (1 << width) - 1;
    return (vertex & mask) == ancestor;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(0, 1000000, "a");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    vector<int> removed;
    removed.reserve(m);

    for (int i = 0; i < m; ++i) {
        int v = inf.readInt(0, 1000000000, "v");
        inf.readEoln();

        if (a < 30) {
            ensuref(v < (1 << a),
                    "v at removal %d does not exist in an age-%d tree: %d",
                    i + 1, a, v);
        }

        for (int j = 0; j < (int)removed.size(); ++j) {
            ensuref(!isAncestor(removed[j], v),
                    "v at removal %d was already removed by removal %d: %d",
                    i + 1, j + 1, v);
        }

        removed.push_back(v);
    }

    inf.readEof();
}
