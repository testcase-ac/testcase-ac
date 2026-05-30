#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(0, N - 1, "M");
    inf.readSpace();
    inf.readInt(1, 10000, "L");
    inf.readEoln();

    vector<int> parent(N);
    iota(parent.begin(), parent.end(), 0);

    auto findRoot = [&](int x) {
        int root = x;
        while (parent[root] != root) {
            root = parent[root];
        }
        while (parent[x] != x) {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        return root;
    };

    set<pair<int, int>> edges;
    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(0, N - 1, "A");
        inf.readSpace();
        int b = inf.readInt(0, N - 1, "B");
        inf.readSpace();
        inf.readInt(1, 10000, "T");
        inf.readEoln();

        ensuref(a != b, "edge %d is a self-loop at %d", i + 1, a);

        pair<int, int> edge = {min(a, b), max(a, b)};
        ensuref(edges.insert(edge).second, "duplicate edge %d between %d and %d",
                i + 1, edge.first, edge.second);

        int ra = findRoot(a);
        int rb = findRoot(b);
        ensuref(ra != rb, "edge %d creates more than one path between %d and %d",
                i + 1, a, b);
        parent[ra] = rb;
    }

    inf.readEof();
}
