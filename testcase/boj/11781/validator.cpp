#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readSpace();
    long long s = inf.readLong(0LL, 1000000000LL, "S");
    inf.readSpace();
    long long e = inf.readLong(1LL, 1000000000LL, "E");
    inf.readEoln();
    ensuref(s < e, "S must be less than E: S=%lld E=%lld", s, e);

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "A");
        inf.readSpace();
        int b = inf.readInt(1, n, "B");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "L");
        inf.readSpace();
        inf.readInt(0, 1, "t1");
        inf.readSpace();
        inf.readInt(0, 1, "t2");
        inf.readEoln();

        ensuref(a != b, "road %d connects the same point: %d", i, a);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<char> seen(n + 1, false);
    queue<int> q;
    seen[1] = true;
    q.push(1);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int next : adj[cur]) {
            if (!seen[next]) {
                seen[next] = true;
                q.push(next);
            }
        }
    }

    for (int v = 1; v <= n; ++v) {
        ensuref(seen[v], "point %d is not connected to point 1", v);
    }

    inf.readEof();
    return 0;
}
