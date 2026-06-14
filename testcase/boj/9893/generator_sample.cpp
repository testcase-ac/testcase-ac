#include "testlib.h"

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    int cost;
};

int randomCost(int limit = (1 << 15) - 1) {
    int mode = rnd.next(0, 4);
    if (mode == 0) return 0;
    if (mode == 1) return rnd.next(0, 5);
    if (mode == 2) return rnd.next(6, 50);
    return rnd.next(0, limit);
}

void addRandomNoise(vector<Edge>& edges, int m, int count) {
    for (int i = 0; i < count; ++i) {
        int from = rnd.next(0, m - 1);
        int to = rnd.next(0, m - 1);
        edges.push_back({from, to, randomCost()});
    }
}

bool reachesOne(const vector<Edge>& edges, int m) {
    vector<vector<int>> graph(m);
    for (const Edge& edge : edges) graph[edge.from].push_back(edge.to);

    vector<bool> seen(m, false);
    queue<int> q;
    seen[0] = true;
    q.push(0);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int next : graph[node]) {
            if (!seen[next]) {
                seen[next] = true;
                q.push(next);
            }
        }
    }
    return seen[1];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int m = rnd.next(2, 14);
    vector<Edge> edges;

    if (mode == 0) {
        edges.push_back({0, 1, randomCost(100)});
        addRandomNoise(edges, m, rnd.next(0, min(25, m * m)));
    } else if (mode == 1) {
        if (m < 3) m = 3;
        int pathCount = rnd.next(2, min(5, m - 1));
        vector<int> middle;
        for (int node = 2; node < m; ++node) middle.push_back(node);
        shuffle(middle.begin(), middle.end());

        for (int i = 0; i < pathCount; ++i) {
            int via = middle[i % (int)middle.size()];
            int first = rnd.next(0, 10);
            int total = rnd.next(first, first + 20);
            edges.push_back({0, via, first});
            edges.push_back({via, 1, total - first});
        }
        addRandomNoise(edges, m, rnd.next(0, 20));
    } else if (mode == 2) {
        if (m < 3) m = 3;
        edges.push_back({0, 1, rnd.next(10, 80)});

        int chainLength = rnd.next(2, min(5, m - 1));
        int previous = 0;
        vector<int> nodes;
        for (int node = 2; node < m; ++node) nodes.push_back(node);
        shuffle(nodes.begin(), nodes.end());

        for (int i = 0; i < chainLength - 1; ++i) {
            int next = nodes[i];
            edges.push_back({previous, next, rnd.next(0, 2)});
            previous = next;
        }
        edges.push_back({previous, 1, rnd.next(0, 2)});
        addRandomNoise(edges, m, rnd.next(0, 18));
    } else if (mode == 3) {
        int layers = rnd.next(2, 4);
        vector<vector<int>> layerNodes(layers);
        layerNodes[0].push_back(0);
        layerNodes[layers - 1].push_back(1);
        for (int node = 2; node < m; ++node) {
            layerNodes[rnd.next(1, layers - 1)].push_back(node);
        }

        for (int layer = 0; layer + 1 < layers; ++layer) {
            for (int from : layerNodes[layer]) {
                for (int to : layerNodes[layer + 1]) {
                    if (rnd.next(0, 99) < 55) edges.push_back({from, to, randomCost(50)});
                }
            }
        }
        edges.push_back({0, layerNodes[1].empty() ? 1 : rnd.any(layerNodes[1]), randomCost(10)});
        if (layers > 2 && !layerNodes[1].empty()) {
            edges.push_back({rnd.any(layerNodes[1]), 1, randomCost(10)});
        }
        addRandomNoise(edges, m, rnd.next(0, 12));
    } else {
        int previous = 0;
        int chainLength = rnd.next(1, min(6, m - 1));
        vector<int> nodes;
        for (int node = 2; node < m; ++node) nodes.push_back(node);
        shuffle(nodes.begin(), nodes.end());

        for (int i = 0; i < chainLength - 1; ++i) {
            int next = nodes[i];
            edges.push_back({previous, next, randomCost(30)});
            previous = next;
        }
        edges.push_back({previous, 1, randomCost(30)});
        addRandomNoise(edges, m, rnd.next(8, min(40, m * m)));
    }

    if (!reachesOne(edges, m)) {
        edges.push_back({0, 1, randomCost(100)});
    }
    if ((int)edges.size() > 1000) edges.resize(1000);
    shuffle(edges.begin(), edges.end());

    println(m, (int)edges.size());
    for (const Edge& edge : edges) {
        println(edge.from, edge.to, edge.cost);
    }

    return 0;
}
