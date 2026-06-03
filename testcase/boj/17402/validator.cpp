#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200, "m");
    inf.readSpace();
    int k = inf.readInt(1, n * m, "k");
    inf.readEoln();

    set<pair<int, int>> marked;
    for (int i = 0; i < k; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, m, "y");
        inf.readEoln();

        ensuref(marked.insert({x, y}).second,
                "duplicate marked cell at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
}
