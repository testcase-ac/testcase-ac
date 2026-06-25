#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

static void addEdge(int a, int b, set<pair<int, int>>& seen, vector<pair<int, int>>& edges) {
    if (a > b) {
        swap(a, b);
    }
    if (a == b || seen.count({a, b})) {
        return;
    }
    seen.insert({a, b});
    edges.push_back({a, b});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 18);
    int k = rnd.next(2, n);

    set<pair<int, int>> seen;
    vector<pair<int, int>> edges;

    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1, seen, edges);
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            addEdge(1, i, seen, edges);
        }
    } else if (mode == 2) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i + 1;
        }
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n; ++i) {
            int parent = order[rnd.next(i)];
            addEdge(order[i], parent, seen, edges);
        }
    } else {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i < split; ++i) {
            addEdge(i, i + 1, seen, edges);
        }
        for (int i = split + 1; i < n; ++i) {
            addEdge(i, i + 1, seen, edges);
        }
        addEdge(rnd.next(1, split), rnd.next(split + 1, n), seen, edges);
    }

    int extraBudget;
    if (mode == 0) {
        extraBudget = rnd.next(0, min(8, n));
    } else if (mode == 1) {
        extraBudget = rnd.next(0, min(10, n * 2));
    } else if (mode == 2) {
        extraBudget = rnd.next(0, min(12, n * 2));
    } else if (mode == 3) {
        extraBudget = rnd.next(0, min(14, n * 3));
    } else {
        int maxExtra = min(n * 3, n * (n - 1) / 2);
        extraBudget = rnd.next(min(n, maxExtra), maxExtra);
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!seen.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());
    extraBudget = min(extraBudget, static_cast<int>(candidates.size()));
    for (int i = 0; i < extraBudget; ++i) {
        addEdge(candidates[i].first, candidates[i].second, seen, edges);
    }

    vector<int> wormholes;
    vector<int> planets(n);
    for (int i = 0; i < n; ++i) {
        planets[i] = i + 1;
    }
    if (rnd.next(2) == 0) {
        wormholes.push_back(1);
    }
    if (static_cast<int>(wormholes.size()) < k && rnd.next(2) == 0) {
        wormholes.push_back(n);
    }
    shuffle(planets.begin(), planets.end());
    for (int planet : planets) {
        if (static_cast<int>(wormholes.size()) == k) {
            break;
        }
        if (find(wormholes.begin(), wormholes.end(), planet) == wormholes.end()) {
            wormholes.push_back(planet);
        }
    }
    shuffle(wormholes.begin(), wormholes.end());
    shuffle(edges.begin(), edges.end());

    println(n, static_cast<int>(edges.size()), k);
    println(wormholes);
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
