#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

static void addEdge(vector<pair<int, int>>& edges, set<pair<int, int>>& used, int u, int v) {
    if (u > v) swap(u, v);
    if (u == v || used.count({u, v})) return;
    used.insert({u, v});
    edges.push_back({u, v});
}

static void addRandomExtraEdges(vector<pair<int, int>>& edges, set<pair<int, int>>& used, int n, int targetM) {
    vector<pair<int, int>> candidates;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (!used.count({u, v})) candidates.push_back({u, v});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (auto edge : candidates) {
        if ((int)edges.size() >= targetM) break;
        addEdge(edges, used, edge.first, edge.second);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    vector<pair<int, int>> edges;
    set<pair<int, int>> used;
    pair<int, int> specialEdge = {1, 2};

    if (mode == 0) {
        for (int v = 2; v <= n; ++v) addEdge(edges, used, v - 1, v);
        specialEdge = edges[rnd.next((int)edges.size())];
    } else if (mode == 1) {
        for (int v = 2; v <= n; ++v) addEdge(edges, used, 1, v);
        specialEdge = edges[rnd.next((int)edges.size())];
    } else if (mode == 2) {
        int left = rnd.next(1, n - 1);
        for (int v = 2; v <= left; ++v) addEdge(edges, used, 1, v);
        for (int v = left + 2; v <= n; ++v) addEdge(edges, used, left + 1, v);
        addEdge(edges, used, left, left + 1);
        specialEdge = edges.back();

        int extra = rnd.next(0, min(6, n * (n - 1) / 2 - (int)edges.size()));
        int targetM = (int)edges.size() + extra;
        addRandomExtraEdges(edges, used, n, targetM);
    } else if (mode == 3) {
        for (int v = 2; v <= n; ++v) addEdge(edges, used, v - 1, v);
        if (n > 2) addEdge(edges, used, 1, n);
        specialEdge = edges[rnd.next((int)edges.size())];
        addRandomExtraEdges(edges, used, n, rnd.next((int)edges.size(), min(n * (n - 1) / 2, (int)edges.size() + 6)));
    } else if (mode == 4) {
        for (int v = 2; v <= n; ++v) addEdge(edges, used, rnd.next(1, v - 1), v);
        int maxM = n * (n - 1) / 2;
        addRandomExtraEdges(edges, used, n, rnd.next((int)edges.size(), min(maxM, n + 8)));
        specialEdge = edges[rnd.next((int)edges.size())];
    } else {
        n = rnd.next(3, 12);
        int maxM = n * (n - 1) / 2;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) addEdge(edges, used, u, v);
        }
        shuffle(edges.begin(), edges.end());
        edges.resize(rnd.next(n - 1, min(maxM, n + 10)));
        used.clear();
        vector<pair<int, int>> compact;
        for (auto edge : edges) addEdge(compact, used, edge.first, edge.second);
        edges = compact;
        for (int v = 2; v <= n; ++v) addEdge(edges, used, 1, v);
        specialEdge = edges[rnd.next((int)edges.size())];
    }

    shuffle(edges.begin(), edges.end());
    int specialIndex = 1;
    for (int i = 0; i < (int)edges.size(); ++i) {
        if (minmax(edges[i].first, edges[i].second) == minmax(specialEdge.first, specialEdge.second)) {
            specialIndex = i + 1;
            break;
        }
    }

    println(n, (int)edges.size(), specialIndex);
    for (auto edge : edges) println(edge.first, edge.second);

    return 0;
}
