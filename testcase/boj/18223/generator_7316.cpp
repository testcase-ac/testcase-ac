#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of vertices between 3 and 10 for hand-checkability
    int V = rnd.next(3, 10);
    // Place P not at endpoints for interest
    int P = rnd.next(2, V - 1);
    // Decide whether this case should be SAVE HIM (true) or GOOD BYE (false)
    bool saveCase = rnd.next(0, 1);

    // Prepare intermediate nodes excluding 1, P, V
    vector<int> rem;
    for (int i = 2; i <= V - 1; i++)
        if (i != P) rem.push_back(i);
    shuffle(rem.begin(), rem.end());
    int t = rnd.next(0, (int)rem.size());
    vector<int> extraNodes(rem.begin(), rem.begin() + t);
    int pre = rnd.next(0, t);
    vector<int> before(extraNodes.begin(), extraNodes.begin() + pre);
    vector<int> after(extraNodes.begin() + pre, extraNodes.end());

    vector<tuple<int,int,int>> edges;
    set<pair<int,int>> used;
    int bestDist = 0;
    int prev = 1;

    // Build the guaranteed shortest path 1 -> ... -> P -> ... -> V
    for (int u : before) {
        int w = rnd.next(1, 10);
        edges.emplace_back(prev, u, w);
        bestDist += w;
        used.insert({min(prev, u), max(prev, u)});
        prev = u;
    }
    {
        int w = rnd.next(1, 10);
        edges.emplace_back(prev, P, w);
        bestDist += w;
        used.insert({min(prev, P), max(prev, P)});
        prev = P;
    }
    for (int u : after) {
        int w = rnd.next(1, 10);
        edges.emplace_back(prev, u, w);
        bestDist += w;
        used.insert({min(prev, u), max(prev, u)});
        prev = u;
    }
    {
        int w = rnd.next(1, 10);
        edges.emplace_back(prev, V, w);
        bestDist += w;
        used.insert({min(prev, V), max(prev, V)});
    }

    // If GOOD BYE case, add a shortcut from 1 to V shorter than bestDist
    if (!saveCase) {
        int w = rnd.next(1, bestDist - 1);
        edges.emplace_back(1, V, w);
        used.insert({1, V});
    }

    // Add some extra edges with high weight so they don't disrupt SAVE HIM cases
    int maxExtra = min(V * (V - 1) / 2 - (int)used.size(), V);
    int extraE = rnd.next(0, maxExtra);
    for (int i = 0; i < extraE; i++) {
        int u, v;
        do {
            u = rnd.next(1, V);
            v = rnd.next(1, V);
            if (u > v) swap(u, v);
        } while (u == v || used.count({u, v}));
        used.insert({u, v});
        // Weight high enough not to create a shorter path
        int w = rnd.next(bestDist, bestDist * 2);
        edges.emplace_back(u, v, w);
    }

    // Shuffle edge order for variability
    shuffle(edges.begin(), edges.end());

    // Output
    int E = edges.size();
    println(V, E, P);
    for (auto &tup : edges) {
        int a, b, c;
        tie(a, b, c) = tup;
        println(a, b, c);
    }
    return 0;
}
