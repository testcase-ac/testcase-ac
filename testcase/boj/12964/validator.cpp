#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
using namespace std;

long long solveMaxScore(const vector<vector<int>>& gA,
                        const vector<vector<int>>& gB,
                        const vector<int>& s) {
    int n = (int)gA.size();
    long long best = (long long)s[0];
    for (int i = 1; i < n; ++i) best = max(best, (long long)s[i]);

    // Enumerate all non-empty subsets S ⊆ {0..n-1}
    int total = 1 << n;
    vector<int> nodes;
    nodes.reserve(n);
    for (int mask = 1; mask < total; ++mask) {
        nodes.clear();
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) nodes.push_back(i);
        }
        int k = (int)nodes.size();

        // check connectivity in A
        {
            queue<int> q;
            vector<char> vis(n, 0);
            q.push(nodes[0]);
            vis[nodes[0]] = 1;
            int cnt = 1;
            while (!q.empty()) {
                int v = q.front(); q.pop();
                for (int to : gA[v]) if (!vis[to] && (mask & (1 << to))) {
                    vis[to] = 1;
                    q.push(to);
                    ++cnt;
                }
            }
            if (cnt != k) continue;
        }

        // check connectivity in B
        {
            queue<int> q;
            vector<char> vis(n, 0);
            q.push(nodes[0]);
            vis[nodes[0]] = 1;
            int cnt = 1;
            while (!q.empty()) {
                int v = q.front(); q.pop();
                for (int to : gB[v]) if (!vis[to] && (mask & (1 << to))) {
                    vis[to] = 1;
                    q.push(to);
                    ++cnt;
                }
            }
            if (cnt != k) continue;
        }

        long long sum = 0;
        for (int v : nodes) sum += s[v];
        if (sum > best) best = sum;
    }
    return best;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 50, "N");
    inf.readEoln();

    vector<vector<int>> gA(N), gB(N);
    set<pair<int,int>> edgesA, edgesB;

    // Read tree A
    for (int i = 0; i < N - 1; ++i) {
        int a = inf.readInt(0, N - 1, "a");
        inf.readSpace();
        int b = inf.readInt(0, N - 1, "b");
        inf.readEoln();

        ensuref(a != b, "Tree A: self-loop at edge %d: (%d, %d)", i, a, b);
        int x = min(a, b), y = max(a, b);
        ensuref(!edgesA.count({x, y}),
                "Tree A: multiple edge detected between %d and %d (at edge %d)", x, y, i);
        edgesA.insert({x, y});
        gA[a].push_back(b);
        gA[b].push_back(a);
    }

    // Check connectivity of tree A
    {
        vector<char> vis(N, 0);
        queue<int> q;
        q.push(0);
        vis[0] = 1;
        int cnt = 1;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int to : gA[v]) if (!vis[to]) {
                vis[to] = 1;
                q.push(to);
                ++cnt;
            }
        }
        ensuref(cnt == N, "Tree A is not connected: reachable %d of %d nodes", cnt, N);
        ensuref((int)edgesA.size() == N - 1,
                "Tree A must have exactly N-1 distinct undirected edges, got %d", (int)edgesA.size());
    }

    // Read tree B
    for (int i = 0; i < N - 1; ++i) {
        int c = inf.readInt(0, N - 1, "c");
        inf.readSpace();
        int d = inf.readInt(0, N - 1, "d");
        inf.readEoln();

        ensuref(c != d, "Tree B: self-loop at edge %d: (%d, %d)", i, c, d);
        int x = min(c, d), y = max(c, d);
        ensuref(!edgesB.count({x, y}),
                "Tree B: multiple edge detected between %d and %d (at edge %d)", x, y, i);
        edgesB.insert({x, y});
        gB[c].push_back(d);
        gB[d].push_back(c);
    }

    // Check connectivity of tree B
    {
        vector<char> vis(N, 0);
        queue<int> q;
        q.push(0);
        vis[0] = 1;
        int cnt = 1;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int to : gB[v]) if (!vis[to]) {
                vis[to] = 1;
                q.push(to);
                ++cnt;
            }
        }
        ensuref(cnt == N, "Tree B is not connected: reachable %d of %d nodes", cnt, N);
        ensuref((int)edgesB.size() == N - 1,
                "Tree B must have exactly N-1 distinct undirected edges, got %d", (int)edgesB.size());
    }

    // Read scores
    vector<int> s(N);
    for (int i = 0; i < N; ++i) {
        s[i] = inf.readInt(-1000, 1000, "s_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    // Problem guarantees that an answer always exists.
    // For safety we can compute it (bruteforce, N<=50 is too large; but this
    // guarantee is trivial: any single vertex subset is valid, so we only
    // need to ensure that we did not misread N=0 which is already forbidden).
    // So no expensive global check is needed here.

    inf.readEof();
}
