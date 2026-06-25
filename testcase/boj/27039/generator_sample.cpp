#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int w;
};

int randomWeight(int mode) {
    if (mode == 0) return rnd.next(1, 12);
    if (mode == 1) return rnd.any(vector<int>{1, 2, 3, 5, 8, 13, 21, 225});
    return rnd.next(1, 225);
}

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int a, int b, int w) {
    if (a > b) swap(a, b);
    if (used.insert({a, b}).second) {
        edges.push_back({a, b, w});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int p = rnd.next(2, mode == 2 ? 14 : 20);
    int n = rnd.next(1, min(30, p * 3));
    int maxEdges = p * (p - 1) / 2;
    int targetEdges = p - 1;

    if (mode == 0) {
        targetEdges = p - 1;
    } else if (mode == 1) {
        targetEdges = rnd.next(p - 1, min(maxEdges, p + rnd.next(0, p)));
    } else if (mode == 2) {
        targetEdges = rnd.next(max(p - 1, maxEdges / 2), maxEdges);
    } else if (mode == 3) {
        targetEdges = rnd.next(p - 1, min(maxEdges, 2 * p));
    } else {
        targetEdges = rnd.next(p - 1, min(maxEdges, p + 5));
    }

    vector<Edge> edges;
    set<pair<int, int>> used;
    int weightMode = rnd.next(0, 2);

    if (mode == 0) {
        for (int i = 1; i < p; ++i) {
            addEdge(edges, used, i, i + 1, randomWeight(weightMode));
        }
    } else if (mode == 1) {
        int hub = rnd.next(1, p);
        for (int v = 1; v <= p; ++v) {
            if (v != hub) addEdge(edges, used, hub, v, randomWeight(weightMode));
        }
    } else if (mode == 3) {
        int split = rnd.next(1, p - 1);
        for (int i = 1; i < split; ++i) {
            addEdge(edges, used, i, i + 1, randomWeight(weightMode));
        }
        for (int i = split + 1; i < p; ++i) {
            addEdge(edges, used, i, i + 1, randomWeight(weightMode));
        }
        addEdge(edges, used, rnd.next(1, split), rnd.next(split + 1, p), randomWeight(weightMode));
    } else {
        vector<int> order;
        for (int i = 1; i <= p; ++i) order.push_back(i);
        shuffle(order.begin(), order.end());
        for (int i = 1; i < p; ++i) {
            int parent = order[rnd.next(0, i - 1)];
            addEdge(edges, used, parent, order[i], randomWeight(weightMode));
        }
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= p; ++a) {
        for (int b = a + 1; b <= p; ++b) {
            if (!used.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (int i = 0; (int)edges.size() < targetEdges && i < (int)candidates.size(); ++i) {
        addEdge(edges, used, candidates[i].first, candidates[i].second, randomWeight(weightMode));
    }
    shuffle(edges.begin(), edges.end());

    vector<int> cows;
    int cowMode = rnd.next(0, 3);
    if (cowMode == 0) {
        int pasture = rnd.next(1, p);
        cows.assign(n, pasture);
    } else if (cowMode == 1) {
        int a = rnd.next(1, p);
        int b = rnd.next(1, p);
        for (int i = 0; i < n; ++i) cows.push_back(rnd.next(0, 1) ? a : b);
    } else {
        int span = rnd.next(1, p);
        for (int i = 0; i < n; ++i) cows.push_back(rnd.next(1, span));
    }

    println(n, p, (int)edges.size());
    for (int cow : cows) println(cow);
    for (const Edge& edge : edges) println(edge.a, edge.b, edge.w);

    return 0;
}
