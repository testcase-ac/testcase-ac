#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void addEdge(vector<string>& g, int u, int v) {
    if (u == v) return;
    g[u][v] = g[v][u] = 'Y';
}

void removeEdge(vector<string>& g, int u, int v) {
    if (u == v) return;
    g[u][v] = g[v][u] = 'N';
}

int pickOther(int n, int a, int b) {
    int x = rnd.next(0, n - 1);
    while (x == a || x == b) x = rnd.next(0, n - 1);
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 5 ? rnd.next(18, 40) : rnd.next(2, 16));
    int a = rnd.next(0, n - 1);
    int b = rnd.next(0, n - 2);
    if (b >= a) ++b;

    vector<string> g(n, string(n, 'N'));

    if (mode == 0) {
        int m = rnd.next(0, min(8, n * (n - 1) / 2));
        vector<pair<int, int>> edges;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if ((i == a && j == b) || (i == b && j == a)) continue;
                edges.push_back({i, j});
            }
        }
        shuffle(edges.begin(), edges.end());
        for (int i = 0; i < m && i < int(edges.size()); ++i) {
            addEdge(g, edges[i].first, edges[i].second);
        }
    } else if (mode == 1) {
        vector<int> v;
        for (int i = 0; i < n; ++i) v.push_back(i);
        shuffle(v.begin(), v.end());
        v.erase(find(v.begin(), v.end(), a));
        v.erase(find(v.begin(), v.end(), b));
        v.insert(v.begin(), a);
        v.push_back(b);
        for (int i = 0; i + 1 < int(v.size()); ++i) {
            addEdge(g, v[i], v[i + 1]);
        }
        if (rnd.next(0, 1) && n > 3) {
            addEdge(g, a, pickOther(n, a, b));
        }
    } else if (mode == 2) {
        int common = rnd.next(0, min(6, n - 2));
        vector<int> nodes;
        for (int i = 0; i < n; ++i) {
            if (i != a && i != b) nodes.push_back(i);
        }
        shuffle(nodes.begin(), nodes.end());
        for (int i = 0; i < common; ++i) {
            addEdge(g, a, nodes[i]);
            addEdge(g, b, nodes[i]);
        }
        for (int i = common; i < int(nodes.size()); ++i) {
            if (rnd.next(0, 2) == 0) addEdge(g, a, nodes[i]);
            if (rnd.next(0, 2) == 0) addEdge(g, b, nodes[i]);
        }
    } else if (mode == 3) {
        vector<int> nodes;
        for (int i = 0; i < n; ++i) {
            if (i != a && i != b) nodes.push_back(i);
        }
        shuffle(nodes.begin(), nodes.end());
        int leftSize = rnd.next(1, max(1, int(nodes.size()) / 2));
        int rightSize = rnd.next(1, max(1, int(nodes.size()) - leftSize));
        vector<int> left(nodes.begin(), nodes.begin() + leftSize);
        vector<int> right(nodes.begin() + leftSize, nodes.begin() + leftSize + rightSize);
        for (int x : left) addEdge(g, a, x);
        for (int x : right) addEdge(g, b, x);
        double p = rnd.next(0.25, 0.85);
        for (int x : left) {
            for (int y : right) {
                if (rnd.next() < p) addEdge(g, x, y);
            }
        }
    } else {
        double p = (mode == 4 ? rnd.next(0.05, 0.35) : rnd.next(0.25, 0.75));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (rnd.next() < p) addEdge(g, i, j);
            }
        }
    }

    removeEdge(g, a, b);

    println(n, a + 1, b + 1);
    for (const string& row : g) println(row);

    return 0;
}
