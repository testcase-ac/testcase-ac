#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 44, "n");
    inf.readSpace();
    int m = inf.readInt(1, 888, "m");
    inf.readEoln();

    int a = inf.readInt(1, n, "a");
    inf.readSpace();
    int b = inf.readInt(1, n, "b");
    inf.readSpace();
    int c = inf.readInt(1, n, "c");
    inf.readEoln();

    ensuref(a != b, "a and b must be distinct: %d", a);
    ensuref(b != c, "b and c must be distinct: %d", b);
    ensuref(a != c, "a and c must be distinct: %d", a);

    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int s = inf.readInt(1, n, "s");
        inf.readSpace();
        int e = inf.readInt(1, n, "e");
        inf.readEoln();

        ensuref(s != e, "self-loop at edge %d: %d %d", i, s, e);
        ensuref(edges.insert({s, e}).second, "duplicate edge at edge %d: %d %d", i, s, e);
    }

    inf.readEof();
}
