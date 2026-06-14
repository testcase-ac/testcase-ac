#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);

    auto findRoot = [&](int v) {
        while (parent[v] != v) {
            parent[v] = parent[parent[v]];
            v = parent[v];
        }
        return v;
    };

    auto unite = [&](int a, int b) {
        a = findRoot(a);
        b = findRoot(b);
        if (a != b) {
            parent[b] = a;
        }
    };

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        int c = inf.readInt(1, 1000, "c");
        inf.readSpace();
        int f = inf.readInt(1, 1000, "f");
        inf.readEoln();

        ensuref(a != b, "pipe %d connects junction %d to itself", i, a);
        (void)c;
        (void)f;
        unite(a, b);
    }

    ensuref(findRoot(1) == findRoot(n), "no path exists from junction 1 to junction N");

    inf.readEof();
}
