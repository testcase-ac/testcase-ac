#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int dataset = 1;
    while (true) {
        int n = inf.readInt(0, 100, "N");
        inf.readSpace();
        int m = inf.readInt(0, 100, "M");
        inf.readSpace();
        int l = inf.readInt(0, 100, "L");
        inf.readSpace();
        // CHECK: K has no explicit upper bound; simple undirected roads imply at most N*(N-1)/2 edges.
        int k = inf.readInt(0, 4950, "K");
        inf.readSpace();
        int a = inf.readInt(0, 100, "A");
        inf.readSpace();
        int h = inf.readInt(0, 100, "H");
        inf.readEoln();

        if (n == 0 && m == 0 && l == 0 && k == 0 && a == 0 && h == 0) {
            break;
        }

        setTestCase(dataset++);

        ensuref(2 <= n && n <= 100, "N must be in [2, 100], found %d", n);
        ensuref(1 <= m && m <= 100, "M must be in [1, 100], found %d", m);
        ensuref(0 <= l && l <= n - 2, "L must be in [0, N-2], found %d with N=%d", l, n);
        ensuref(0 <= a && a < n, "A must be in [0, N-1], found %d with N=%d", a, n);
        ensuref(0 <= h && h < n, "H must be in [0, N-1], found %d with N=%d", h, n);
        ensuref(a != h, "A and H must be different, both are %d", a);
        ensuref(k <= n * (n - 1) / 2, "K=%d exceeds the number of simple undirected roads for N=%d", k, n);

        vector<bool> freezer(n, false);
        for (int i = 0; i < l; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            int town = inf.readInt(0, n - 1, "freezer_town");
            ensuref(town != a && town != h, "freezer town %d must not be A=%d or H=%d", town, a, h);
            ensuref(!freezer[town], "duplicate freezer town %d", town);
            freezer[town] = true;
        }
        if (l > 0) {
            inf.readEoln();
        }

        set<pair<int, int>> roads;
        for (int i = 0; i < k; ++i) {
            int x = inf.readInt(0, n - 1, "X");
            inf.readSpace();
            int y = inf.readInt(0, n - 1, "Y");
            inf.readSpace();
            // CHECK: T has no explicit upper bound; cap it at 1e9 to keep numeric inputs practical.
            int t = inf.readInt(0, 1000000000, "T");
            inf.readEoln();

            // CHECK: The statement describes roads between towns and says each pair has at most one road.
            ensuref(x != y, "road %d is a self-loop at town %d", i + 1, x);
            auto edge = minmax(x, y);
            ensuref(roads.insert(edge).second, "duplicate road between towns %d and %d", edge.first, edge.second);
        }
    }

    inf.readEof();
}
