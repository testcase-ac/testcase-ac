#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
    int w;
};

int weightForMode(int mode) {
    if (mode == 0) {
        return rnd.next(1, 12);
    }
    if (mode == 1) {
        return rnd.next(1, 3);
    }
    if (mode == 2) {
        return rnd.next(50, 100000);
    }
    return rnd.next(1, 100000);
}

void addEdge(vector<Edge>& edges, int u, int v, int mode) {
    edges.push_back({u, v, weightForMode(mode)});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(2, mode == 3 ? 16 : 12);
    int k = rnd.next(1, n);

    vector<int> cities(n);
    iota(cities.begin(), cities.end(), 1);
    shuffle(cities.begin(), cities.end());

    vector<int> interviews(cities.begin(), cities.begin() + k);
    vector<int> others(cities.begin() + k, cities.end());
    shuffle(interviews.begin(), interviews.end());
    shuffle(others.begin(), others.end());

    vector<Edge> edges;

    if (mode == 0) {
        int sink = interviews[0];
        int prev = sink;
        for (int city : others) {
            addEdge(edges, city, prev, mode);
            prev = city;
        }
    } else if (mode == 1) {
        for (int city : others) {
            addEdge(edges, city, rnd.any(interviews), mode);
        }
    } else {
        vector<int> reachable = interviews;
        for (int city : others) {
            int parent = rnd.any(reachable);
            addEdge(edges, city, parent, mode);
            reachable.push_back(city);
        }
    }

    int maxEdges = min(n * (n - 1), mode == 3 ? 55 : 30);
    int targetEdges = rnd.next(max(1, (int)edges.size()), maxEdges);
    while ((int)edges.size() < targetEdges) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n - 1);
        if (v >= u) {
            ++v;
        }
        addEdge(edges, u, v, mode);
    }

    if (rnd.next(0, 3) == 0 && !edges.empty() && (int)edges.size() < n * (n - 1)) {
        Edge duplicate = rnd.any(edges);
        duplicate.w = weightForMode(mode);
        edges.push_back(duplicate);
    }

    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size(), k);
    for (const Edge& edge : edges) {
        println(edge.u, edge.v, edge.w);
    }
    println(interviews);

    return 0;
}
