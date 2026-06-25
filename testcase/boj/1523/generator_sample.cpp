#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 15);
    int mode = n == 1 ? 0 : rnd.next(0, 6);

    vector<string> adj(n, string(n, '0'));

    auto addEdge = [&](int u, int v) {
        if (u == v) return;
        adj[u][v] = '1';
        adj[v][u] = '1';
    };

    if (mode == 1) {
        int center = rnd.next(n);
        for (int v = 0; v < n; ++v) {
            if (v != center) addEdge(center, v);
        }
    } else if (mode == 2) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n; ++i) addEdge(order[i - 1], order[i]);
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) addEdge(i, j);
        }
    } else if (mode == 4) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        shuffle(order.begin(), order.end());
        for (int i = 0; i < n; ++i) addEdge(order[i], order[(i + 1) % n]);
    } else {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        shuffle(order.begin(), order.end());

        for (int i = 1; i < n; ++i) {
            addEdge(order[i], order[rnd.next(0, i - 1)]);
        }

        vector<pair<int, int>> extras;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (adj[i][j] == '0') extras.push_back({i, j});
            }
        }
        shuffle(extras.begin(), extras.end());

        int addCount = rnd.next(0, (int)extras.size());
        if (!extras.empty() && rnd.next(0, 2) == 0) {
            addCount = rnd.wnext((int)extras.size() + 1, rnd.next(-2, 2));
        }
        for (int i = 0; i < addCount; ++i) addEdge(extras[i].first, extras[i].second);
    }

    println(n);
    for (const string& row : adj) println(row);

    return 0;
}
