#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using Edge = pair<int, int>;

static Edge normalized(int a, int b) {
    if (a > b) swap(a, b);
    return {a, b};
}

static void addEdge(vector<Edge>& edges, set<Edge>& used, int a, int b) {
    Edge e = normalized(a, b);
    if (used.insert(e).second) edges.push_back(e);
}

static vector<Edge> allCandidateEdges(int n) {
    vector<Edge> candidates;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            candidates.push_back({i, j});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    return candidates;
}

static void addRandomEdges(vector<Edge>& edges, set<Edge>& used, int n, int target) {
    vector<Edge> candidates = allCandidateEdges(n);
    for (Edge e : candidates) {
        if ((int)edges.size() >= target) break;
        addEdge(edges, used, e.first, e.second);
    }
}

static void printGraph(int n, vector<Edge> edges) {
    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (Edge e : edges) println(e.first, e.second);
}

static void makeConnected(int n, vector<Edge>& edges, set<Edge>& used) {
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());
    for (int i = 1; i < n; ++i) {
        int parent = order[rnd.next(i)];
        addEdge(edges, used, parent, order[i]);
    }
}

static vector<Edge> makeCycleComponent(int start, int len) {
    vector<Edge> component;
    for (int i = 0; i < len; ++i) {
        int a = start + i;
        int b = start + ((i + 1) % len);
        component.push_back(normalized(a, b));
    }
    return component;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<Edge> edges;
    set<Edge> used;
    int n;

    if (mode == 0) {
        n = rnd.next(3, 12);
        makeConnected(n, edges, used);
        addEdge(edges, used, 1, n);
        addRandomEdges(edges, used, n, rnd.next(n, min(n + 5, n * (n - 1) / 2)));
    } else if (mode == 1) {
        n = rnd.next(4, 12);
        makeConnected(n, edges, used);
        addRandomEdges(edges, used, n, rnd.next(n, min(n + 7, n * (n - 1) / 2)));
    } else if (mode == 2) {
        n = rnd.next(6, 12);
        int first = rnd.next(3, n - 3);
        vector<Edge> left = makeCycleComponent(1, first);
        vector<Edge> right = makeCycleComponent(first + 1, n - first);
        for (Edge e : left) addEdge(edges, used, e.first, e.second);
        for (Edge e : right) addEdge(edges, used, e.first, e.second);
        if (rnd.next(0, 1)) {
            addEdge(edges, used, 1, first / 2 + 1);
            addEdge(edges, used, first + 1, first + 2);
        }
    } else {
        n = rnd.next(5, 12);
        int maxEdges = n * (n - 1) / 2;
        addRandomEdges(edges, used, n, rnd.next(n + 2, min(maxEdges, n + 16)));
        vector<int> degree(n + 1, 0);
        for (Edge e : edges) {
            ++degree[e.first];
            ++degree[e.second];
        }
        for (int i = 1; i <= n; ++i) {
            if (degree[i] == 0) {
                int to = rnd.next(1, n - 1);
                if (to >= i) ++to;
                addEdge(edges, used, i, to);
            }
        }
    }

    printGraph(n, edges);
    return 0;
}
