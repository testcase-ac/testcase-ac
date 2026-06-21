#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

void addEdge(vector<Edge>& edges, int a, int b) {
    if (a > b) swap(a, b);
    edges.push_back({a, b});
}

vector<Edge> makeTree(int n, int mode) {
    vector<Edge> edges;

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) addEdge(edges, v - 1, v);
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) addEdge(edges, 1, v);
    } else if (mode == 2) {
        for (int v = 2; v <= n; ++v) addEdge(edges, max(1, v / 2), v);
    } else if (mode == 3) {
        int spine = rnd.next(2, max(2, n / 2));
        for (int v = 2; v <= spine; ++v) addEdge(edges, v - 1, v);
        for (int v = spine + 1; v <= n; ++v) addEdge(edges, rnd.next(1, spine), v);
    } else {
        for (int v = 2; v <= n; ++v) addEdge(edges, rnd.next(1, v - 1), v);
    }

    shuffle(edges.begin(), edges.end());
    return edges;
}

vector<int> makePermutation(int n, const vector<Edge>& edges, int mode) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);

    if (mode == 0) {
        return order;
    }
    if (mode == 1) {
        reverse(order.begin(), order.end());
        return order;
    }
    if (mode == 2) {
        shuffle(order.begin(), order.end());
        return order;
    }

    vector<vector<int>> graph(n + 1);
    for (auto [a, b] : edges) {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<bool> used(n + 1, false);
    vector<int> perm;
    int current = rnd.next(1, n);

    while (static_cast<int>(perm.size()) < n) {
        used[current] = true;
        perm.push_back(current);

        vector<int> dist(n + 1, -1);
        queue<int> q;
        dist[current] = 0;
        q.push(current);
        vector<int> close;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if (dist[v] == 3) continue;
            for (int to : graph[v]) {
                if (dist[to] != -1) continue;
                dist[to] = dist[v] + 1;
                q.push(to);
                if (!used[to]) close.push_back(to);
            }
        }

        if (!close.empty() && rnd.next(0, 4) != 0) {
            current = rnd.any(close);
            continue;
        }

        vector<int> remaining;
        for (int v = 1; v <= n; ++v) {
            if (!used[v]) remaining.push_back(v);
        }
        if (!remaining.empty()) current = rnd.any(remaining);
    }

    return perm;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int treeMode = tc < 5 ? tc : rnd.next(0, 4);
        int permMode = rnd.next(0, 3);
        int n = rnd.next(2, 14);
        if (treeMode == 2) n = rnd.next(3, 15);

        vector<Edge> edges = makeTree(n, treeMode);
        vector<int> permutation = makePermutation(n, edges, permMode);

        println(n);
        for (auto [a, b] : edges) println(a, b);
        for (int value : permutation) println(value);
    }

    return 0;
}
