#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(int u, int v, vector<int>& degree, set<pair<int, int>>& edges) {
    if (u == v) return;
    if (u > v) swap(u, v);
    if (degree[u] >= 3 || degree[v] >= 3) return;
    if (!edges.insert({u, v}).second) return;
    ++degree[u];
    ++degree[v];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 24);
    if (mode == 1) n = rnd.next(2, 12);
    if (mode == 2) n = rnd.next(4, 18);
    if (mode == 3) n = 4;

    vector<int> degree(n + 1, 0);
    set<pair<int, int>> edges;

    if (mode == 0) {
        int pairs = rnd.next(0, n / 2);
        vector<int> vertices;
        for (int i = 1; i <= n; ++i) vertices.push_back(i);
        shuffle(vertices.begin(), vertices.end());
        for (int i = 0; i < 2 * pairs; i += 2) {
            addEdge(vertices[i], vertices[i + 1], degree, edges);
        }
    } else if (mode == 1) {
        vector<int> vertices;
        for (int i = 1; i <= n; ++i) vertices.push_back(i);
        shuffle(vertices.begin(), vertices.end());
        for (int i = 1; i < n; ++i) {
            addEdge(vertices[i - 1], vertices[i], degree, edges);
        }
    } else if (mode == 2) {
        vector<int> vertices;
        for (int i = 1; i <= n; ++i) vertices.push_back(i);
        shuffle(vertices.begin(), vertices.end());
        for (int i = 0; i < n; ++i) {
            addEdge(vertices[i], vertices[(i + 1) % n], degree, edges);
        }
        int chords = rnd.next(0, n / 2);
        for (int i = 0; i < chords; ++i) {
            int at = rnd.next(0, n - 1);
            addEdge(vertices[at], vertices[(at + rnd.next(2, n - 2)) % n], degree, edges);
        }
    } else if (mode == 3) {
        addEdge(1, 2, degree, edges);
        addEdge(1, 3, degree, edges);
        addEdge(1, 4, degree, edges);
        addEdge(2, 3, degree, edges);
        addEdge(2, 4, degree, edges);
        addEdge(3, 4, degree, edges);
    } else {
        vector<pair<int, int>> candidates;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                candidates.push_back({i, j});
            }
        }
        shuffle(candidates.begin(), candidates.end());

        int target = rnd.next(0, (3 * n) / 2);
        if (mode == 5) target = rnd.next(n / 2, (3 * n) / 2);
        for (auto [u, v] : candidates) {
            if ((int)edges.size() >= target) break;
            if (mode == 4 && rnd.next(0, 99) >= 35) continue;
            addEdge(u, v, degree, edges);
        }
    }

    vector<pair<int, int>> output(edges.begin(), edges.end());
    println(n, (int)output.size());
    for (auto [u, v] : output) {
        println(u, v);
    }

    return 0;
}
