#include "testlib.h"
#include <vector>
#include <set>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and C
    int N = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int C = inf.readInt(1, 1000000, "C");
    inf.readEoln();

    // Read N points, check bounds and uniqueness
    vector<pair<int, int>> points(N);
    set<pair<int, int>> seen;
    for (int i = 0; i < N; ++i) {
        int x = inf.readInt(0, 1000, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, 1000, "y_i");
        inf.readEoln();
        ensuref(seen.count({x, y}) == 0, "Duplicate point at index %d: (%d, %d)", i+1, x, y);
        seen.insert({x, y});
        points[i] = {x, y};
    }

    // Check that the graph with edges of cost >= C is connected
    // Build adjacency list
    vector<vector<int>> adj(N);
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            long long dx = points[i].first - points[j].first;
            long long dy = points[i].second - points[j].second;
            long long dist2 = dx*dx + dy*dy;
            if (dist2 >= C) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    // BFS/DFS to check connectivity
    vector<bool> vis(N, false);
    vector<int> stack;
    stack.push_back(0);
    vis[0] = true;
    while (!stack.empty()) {
        int u = stack.back(); stack.pop_back();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                stack.push_back(v);
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < N; ++i) if (vis[i]) ++cnt;
    ensuref(cnt == N, "The graph with edges of cost >= C is not connected");

    inf.readEof();
}
