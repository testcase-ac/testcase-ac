#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 1000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 3000, "K");
    inf.readEoln();

    vector<vector<int>> usable(n + 2);

    for (int i = 0; i < k; ++i) {
        int u = inf.readInt(0, n + 1, "u");
        inf.readSpace();
        int v = inf.readInt(0, n + 1, "v");
        inf.readSpace();
        int t = inf.readInt(1, 1000, "t");
        inf.readEoln();

        // CHECK: A road connects two positions, so a self-loop is not a road.
        ensuref(u != v, "road %d is a self-loop at %d", i + 1, u);

        if (t <= 100) {
            usable[u].push_back(v);
            usable[v].push_back(u);
        }
    }

    vector<int> seen(n + 2);
    queue<int> q;
    seen[0] = 1;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : usable[u]) {
            if (!seen[v]) {
                seen[v] = 1;
                q.push(v);
            }
        }
    }

    ensuref(seen[n + 1], "settlements are not connected by roads with travel time at most 100");

    inf.readEof();
}
