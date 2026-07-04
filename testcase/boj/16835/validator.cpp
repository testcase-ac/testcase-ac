#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    int s = inf.readInt(1, n, "S");
    inf.readSpace();
    int t = inf.readInt(1, n, "T");
    inf.readEoln();

    ensuref(s != t, "S and T must be different: %d", s);

    vector<vector<int>> graph(n + 1);
    set<pair<int, int>> edges;
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a < b, "edge %d must satisfy a_i < b_i, got %d %d", i, a, b);
        ensuref(edges.insert({a, b}).second, "duplicate edge %d: %d %d", i, a, b);

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> stack = {t};
    vector<char> seen(n + 1, false);
    seen[t] = true;
    for (int index = 0; index < (int)stack.size(); ++index) {
        int v = stack[index];
        for (int next : graph[v]) {
            if (!seen[next]) {
                seen[next] = true;
                stack.push_back(next);
            }
        }
    }

    for (int v = 1; v <= n; ++v) {
        ensuref(seen[v], "computer %d is not reachable to T=%d", v, t);
    }

    inf.readEof();
}
