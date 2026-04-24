#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read target average a/b from input
    int a = inf.readInt();
    inf.readChar('/'); 
    int b = inf.readInt();

    // Read jury answer to know if solution exists
    bool juryImpossible = false;
    string sAns = ans.readToken();
    if (sAns == "impossible") {
        juryImpossible = true;
    }
    // We don't need to consume the rest of jury's graph

    // Read participant's first token
    if (juryImpossible) {
        // Expect participant to also say impossible
        string sP = ouf.readToken();
        if (sP != "impossible") {
            quitf(_wa, "participant should output \"impossible\"");
        }
        // No extra output
        if (!ouf.seekEof()) {
            quitf(_wa, "extra output after \"impossible\"");
        }
        quitf(_ok, "both impossible");
    } else {
        // Solution exists, participant must output a graph
        string sP = ouf.readToken();
        if (sP == "impossible") {
            quitf(_wa, "solution exists, but participant says impossible");
        }
        // Parse n
        for (char c : sP) {
            if (!isdigit(c)) {
                quitf(_wa, "invalid number of vertices: \"%s\"", sP.c_str());
            }
        }
        int n;
        try {
            n = stoi(sP);
        } catch (...) {
            quitf(_wa, "number of vertices out of range: \"%s\"", sP.c_str());
        }
        if (n < 1 || n > 1000000) {
            quitf(_wa, "number of vertices %d is out of bounds [1,1e6]", n);
        }
        // Read m
        int m = ouf.readInt(1, 1000000, "number of edges");
        // Read edges
        vector<vector<int>> adj(n+1);
        adj.reserve(n+1);
        for (int i = 0; i < m; i++) {
            int u = ouf.readInt(1, n, format("edge %d: endpoint u", i+1).c_str());
            int v = ouf.readInt(1, n, format("edge %d: endpoint v", i+1).c_str());
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        // No extra output
        if (!ouf.seekEof()) {
            quitf(_wa, "extra output after graph");
        }
        // BFS from vertex 1
        vector<int> dist(n+1, -1);
        queue<int> q;
        dist[1] = 0;
        q.push(1);
        ll sumDist = 0;
        int visited = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    sumDist += dist[v];
                    visited++;
                    q.push(v);
                }
            }
        }
        if (visited != n) {
            quitf(_wa, "graph is not connected: reachable %d out of %d vertices", visited, n);
        }
        // Check average: sumDist / n == a / b  =>  sumDist * b == a * n
        ll lhs = sumDist * (ll)b;
        ll rhs = (ll)a * (ll)n;
        if (lhs != rhs) {
            quitf(_wa, "wrong average: expected %d/%d, found %lld/%d",
                  a, b, sumDist, (ll)n);
        }
        quitf(_ok, "valid graph with average %d/%d", a, b);
    }
    return 0;
}
