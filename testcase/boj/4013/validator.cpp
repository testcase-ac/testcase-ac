#include "testlib.h"
#include <queue>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 500000, "M");
    inf.readEoln();

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();
        adj[u].push_back(v);
    }

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 4000, "cash_i");
        inf.readEoln();
    }

    int s = inf.readInt(1, n, "S");
    inf.readSpace();
    int p = inf.readInt(1, n, "P");
    inf.readEoln();

    vector<int> restaurants = inf.readInts(p, 1, n, "restaurant");
    inf.readEoln();
    vector<char> isRestaurant(n + 1, false);
    for (int i = 0; i < p; ++i) {
        int restaurant = restaurants[i];
        ensuref(!isRestaurant[restaurant],
                "duplicate restaurant at position %d: %d", i + 1, restaurant);
        isRestaurant[restaurant] = true;
    }

    vector<char> reachable(n + 1, false);
    queue<int> q;
    reachable[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (!reachable[v]) {
                reachable[v] = true;
                q.push(v);
            }
        }
    }

    bool hasReachableRestaurant = false;
    for (int restaurant : restaurants) {
        hasReachableRestaurant |= reachable[restaurant];
    }
    ensuref(hasReachableRestaurant, "no restaurant is reachable from S=%d", s);

    inf.readEof();
}
