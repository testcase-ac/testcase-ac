#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n, m, s, t;
vector<vector<int>> adj;
vector<int> cost;

// This function reads a set of tollgates from the given stream,
// checks that they are a valid s-t vertex cut, computes and returns
// the total cost. If something is wrong in the contestant output,
// it quits with _wa; if something is wrong in the jury output,
// it quits with _fail (stream.quitf handles that automatically).
long long readAnsStream(InStream &stream) {
    vector<int> rem;
    // Read all integers (tollgate indices) until EOF
    while (true) {
        stream.skipBlanks();
        if (stream.eof()) break;
        int v = stream.readInt(1, n, "tollgate number");
        rem.push_back(v);
    }
    // Check that the list is strictly increasing (ascending & no duplicates)
    for (int i = 1; i < (int)rem.size(); i++) {
        if (rem[i] <= rem[i-1]) {
            stream.quitf(_wa,
                "tollgates not in strictly ascending order at position %d: found %d after %d",
                i+1, rem[i], rem[i-1]);
        }
    }
    // Mark blocked vertices
    vector<char> blocked(n+1, 0);
    for (int v : rem) blocked[v] = 1;
    // Run BFS from s avoiding blocked nodes
    vector<char> vis(n+1, 0);
    queue<int> q;
    if (!blocked[s]) {
        vis[s] = 1;
        q.push(s);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int w : adj[u]) {
            if (!vis[w] && !blocked[w]) {
                vis[w] = 1;
                q.push(w);
            }
        }
    }
    // If t is still reachable, it's not a cut
    if (vis[t]) {
        stream.quitf(_wa, "mafia can still travel from %d to %d", s, t);
    }
    // Compute total cost
    long long sum = 0;
    for (int v : rem) sum += cost[v];
    return sum;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    n = inf.readInt();
    m = inf.readInt();
    s = inf.readInt();
    t = inf.readInt();
    cost.assign(n+1, 0);
    for (int i = 1; i <= n; i++) {
        cost[i] = inf.readInt(1, 10000000);
    }
    adj.assign(n+1, vector<int>());
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n);
        int v = inf.readInt(1, n);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // Read jury and participant answers
    long long jans = readAnsStream(ans);
    long long pans = readAnsStream(ouf);
    // Ensure no extra tokens in participant output
    ouf.readEof();
    // Compare costs
    if (pans > jans) {
        quitf(_wa, "total cost is too large: participant = %lld, jury = %lld", pans, jans);
    } else if (pans < jans) {
        quitf(_fail, "participant paid less than jury: participant = %lld, jury = %lld", pans, jans);
    } else {
        quitf(_ok, "total cost = %lld", pans);
    }
    return 0;
}
