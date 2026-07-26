#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    vector<int> parent(n + 1);
    iota(parent.begin(), parent.end(), 0);
    auto find = [&](auto&& self, int x) -> int {
        return parent[x] == x ? x : parent[x] = self(self, parent[x]);
    };

    for (int i = 0; i < n - 1; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();
        a = find(find, a);
        b = find(find, b);
        ensuref(a != b, "edge %d creates a cycle", i + 1);
        parent[a] = b;
    }

    for (int i = 0; i < m; ++i) {
        inf.readInt(1, n, "c_i");
        inf.readSpace();
        inf.readInt(0, n - 1, "d_i");
        inf.readSpace();
        inf.readInt(1, 1000000000, "g_i");
        inf.readEoln();
    }

    inf.readEof();
}
