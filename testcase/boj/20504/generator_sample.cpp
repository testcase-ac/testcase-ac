#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(set<pair<int, int>>& edges, int u, int v) {
    edges.insert({u, v});
}

void addCycle(set<pair<int, int>>& edges, const vector<int>& nodes) {
    if (nodes.size() == 1) {
        addEdge(edges, nodes[0], nodes[0]);
        return;
    }
    for (int i = 0; i < (int)nodes.size(); ++i) {
        addEdge(edges, nodes[i], nodes[(i + 1) % nodes.size()]);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 14);
    set<pair<int, int>> edges;
    vector<int> tests;

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(0, 1)) addEdge(edges, i, i);
        }
        if (edges.empty()) addEdge(edges, rnd.next(1, n), rnd.next(1, n));

        vector<int> nodes(n);
        for (int i = 0; i < n; ++i) nodes[i] = i + 1;
        shuffle(nodes.begin(), nodes.end());
        int t = rnd.next(1, n);
        tests.assign(nodes.begin(), nodes.begin() + t);
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        for (int v = 2; v <= n; ++v) {
            if (rnd.next(0, 99) < 70) addEdge(edges, rnd.next(1, v - 1), v);
        }
        if (edges.empty()) addEdge(edges, 1, 2);
        if (rnd.next(0, 1)) addEdge(edges, rnd.next(1, n), rnd.next(1, n));

        vector<int> nodes(n);
        for (int i = 0; i < n; ++i) nodes[i] = i + 1;
        shuffle(nodes.begin(), nodes.end());
        int t = rnd.next(1, n);
        tests.assign(nodes.begin(), nodes.begin() + t);
    } else if (mode == 2) {
        n = rnd.next(6, 14);
        vector<int> nodes(n);
        for (int i = 0; i < n; ++i) nodes[i] = i + 1;
        shuffle(nodes.begin(), nodes.end());

        int pos = 0;
        vector<vector<int>> comps;
        while (pos < n) {
            int remaining = n - pos;
            int sz = rnd.next(1, min(4, remaining));
            comps.push_back(vector<int>(nodes.begin() + pos, nodes.begin() + pos + sz));
            addCycle(edges, comps.back());
            pos += sz;
        }
        for (int i = 0; i + 1 < (int)comps.size(); ++i) {
            if (rnd.next(0, 99) < 80) addEdge(edges, rnd.any(comps[i]), rnd.any(comps[i + 1]));
            if (i + 2 < (int)comps.size() && rnd.next(0, 99) < 35) {
                addEdge(edges, rnd.any(comps[i]), rnd.any(comps[i + 2]));
            }
        }

        for (const auto& comp : comps) {
            if (rnd.next(0, 99) < 65) tests.push_back(rnd.any(comp));
        }
        if (tests.empty()) tests.push_back(rnd.next(1, n));
    } else if (mode == 3) {
        n = rnd.next(4, 12);
        int sourceCount = rnd.next(2, min(4, n - 1));
        for (int s = 1; s <= sourceCount; ++s) {
            for (int v = sourceCount + 1; v <= n; ++v) {
                if (rnd.next(0, 99) < 45) addEdge(edges, s, v);
            }
        }
        for (int u = sourceCount + 1; u <= n; ++u) {
            for (int v = sourceCount + 1; v <= n; ++v) {
                if (u != v && rnd.next(0, 99) < 18) addEdge(edges, u, v);
            }
        }
        if (edges.empty()) addEdge(edges, 1, sourceCount + 1);

        vector<int> nodes(n);
        for (int i = 0; i < n; ++i) nodes[i] = i + 1;
        shuffle(nodes.begin(), nodes.end());
        int t = rnd.next(1, n);
        tests.assign(nodes.begin(), nodes.begin() + t);
    } else {
        n = rnd.next(5, 10);
        int targetM = rnd.next(n, min(n * n, 30));
        while ((int)edges.size() < targetM) {
            addEdge(edges, rnd.next(1, n), rnd.next(1, n));
        }

        vector<int> nodes(n);
        for (int i = 0; i < n; ++i) nodes[i] = i + 1;
        shuffle(nodes.begin(), nodes.end());
        int t = rnd.next(1, n);
        tests.assign(nodes.begin(), nodes.begin() + t);
    }

    sort(tests.begin(), tests.end());
    tests.erase(unique(tests.begin(), tests.end()), tests.end());
    if (tests.empty()) tests.push_back(1);
    shuffle(tests.begin(), tests.end());

    vector<pair<int, int>> edgeList(edges.begin(), edges.end());
    shuffle(edgeList.begin(), edgeList.end());

    println(n, (int)edgeList.size());
    for (auto [u, v] : edgeList) {
        println(u, v);
    }
    println((int)tests.size());
    for (int x : tests) {
        println(x);
    }

    return 0;
}
