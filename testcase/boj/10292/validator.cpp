#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 15, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 30000, "N");
        inf.readSpace();
        int m = inf.readInt(0, 300000, "M");
        inf.readEoln();

        vector<vector<int>> graph(n + 1);
        set<pair<int, int>> edges;

        for (int i = 1; i <= m; ++i) {
            int a = inf.readInt(1, n, "A");
            inf.readSpace();
            int b = inf.readInt(1, n, "B");
            inf.readEoln();

            ensuref(a != b, "edge %d is a self-loop: %d %d", i, a, b);

            pair<int, int> edge = minmax(a, b);
            // CHECK: The statement counts M friendships; parallel entries would
            // describe the same friendship more than once.
            ensuref(edges.insert(edge).second,
                    "duplicate friendship at edge %d: %d %d", i, a, b);

            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        vector<int> stack = {1};
        vector<char> seen(n + 1, false);
        seen[1] = true;
        int reached = 0;

        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            ++reached;

            for (int to : graph[v]) {
                if (!seen[to]) {
                    seen[to] = true;
                    stack.push_back(to);
                }
            }
        }

        ensuref(reached == n,
                "test case graph must be connected, reached %d of %d nodes",
                reached, n);
    }

    inf.readEof();
}
