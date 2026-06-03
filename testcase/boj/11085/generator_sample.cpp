#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int width;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int p = rnd.next(2, mode == 4 ? 14 : 10);

    vector<int> label(p);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin(), label.end());

    int c = label[0];
    int v = label[1];

    vector<Edge> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int a, int b, int lo, int hi) {
        if (a == b) {
            return;
        }
        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        int x = min(a, b);
        int y = max(a, b);
        if (!used.insert({x, y}).second) {
            return;
        }
        edges.push_back({a, b, rnd.next(lo, hi)});
    };

    if (mode == 0) {
        addEdge(c, v, 1, 1000);
    } else {
        int pathLen = rnd.next(2, min(p, mode == 1 ? 4 : 7));
        vector<int> path;
        path.push_back(c);
        for (int i = 2; (int)path.size() + 1 < pathLen; ++i) {
            path.push_back(label[i]);
        }
        path.push_back(v);

        int bottleneck = rnd.next(1, 1000);
        for (int i = 1; i < (int)path.size(); ++i) {
            int lo = mode == 2 ? bottleneck : 1;
            addEdge(path[i - 1], path[i], lo, 1000);
        }

        if (mode == 2 && path.size() > 2) {
            int pos = rnd.next(1, (int)path.size() - 1);
            int a = path[pos - 1];
            int b = path[pos];
            for (Edge& edge : edges) {
                if (min(edge.a, edge.b) == min(a, b) && max(edge.a, edge.b) == max(a, b)) {
                    edge.width = bottleneck;
                }
            }
        }
    }

    int targetEdges = (mode == 4) ? rnd.next(p - 1, min(3 * p, p * (p - 1) / 2))
                                  : rnd.next((int)edges.size(), min(2 * p, p * (p - 1) / 2));

    vector<pair<int, int>> candidates;
    for (int i = 0; i < p; ++i) {
        for (int j = i + 1; j < p; ++j) {
            if (!used.count({i, j})) {
                candidates.push_back({i, j});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    for (pair<int, int> candidate : candidates) {
        if ((int)edges.size() >= targetEdges) {
            break;
        }
        int lo = (mode == 3) ? 1 : rnd.next(1, 800);
        int hi = (mode == 3) ? rnd.next(lo, 1000) : 1000;
        addEdge(candidate.first, candidate.second, lo, hi);
    }

    shuffle(edges.begin(), edges.end());

    println(p, (int)edges.size());
    println(c, v);
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.width);
    }

    return 0;
}
