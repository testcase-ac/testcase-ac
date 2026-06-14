#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 5000, "M");
    inf.readEoln();

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(a + 1, n, "B");
        inf.readEoln();

        ensuref(edges.insert({a, b}).second,
                "duplicate edge at index %d: (%d, %d)", i, a, b);
    }

    inf.readEof();
}
