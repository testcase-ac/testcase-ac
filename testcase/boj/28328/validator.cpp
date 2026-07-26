#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 250000, "n");
    inf.readEoln();

    vector<int> parent(n + 1);
    vector<int> component_size(n + 1, 1);
    iota(parent.begin(), parent.end(), 0);
    auto find = [&](auto&& self, int x) -> int {
        return parent[x] == x ? x : parent[x] = self(self, parent[x]);
    };

    for (int i = 0; i < n - 1; ++i) {
        int u = inf.readInt(1, n, "u");
        inf.readSpace();
        int v = inf.readInt(1, n, "v");
        inf.readEoln();

        ensuref(u != v, "edge %d is a self-loop at vertex %d", i + 1, u);
        u = find(find, u);
        v = find(find, v);
        ensuref(u != v, "edge %d creates a cycle", i + 1);
        if (component_size[u] < component_size[v]) {
            parent[u] = v;
            component_size[v] += component_size[u];
        } else {
            parent[v] = u;
            component_size[u] += component_size[v];
        }
    }

    inf.readEof();
}
