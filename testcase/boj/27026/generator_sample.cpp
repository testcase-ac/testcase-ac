#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;

    bool operator<(const Point& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }
};

struct Edge {
    int u;
    int v;
    int len;
    char dir;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<pair<int, int>> delta = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    const string dirs = "NESW";

    int n = rnd.next(2, 24);
    int step = rnd.next(1, 12);

    vector<Point> pos(n + 1);
    vector<array<int, 4>> usedDir(n + 1);
    map<Point, int> farmAt;
    vector<Edge> edges;

    pos[1] = {0, 0};
    farmAt[pos[1]] = 1;

    for (int farm = 2; farm <= n; ++farm) {
        vector<pair<int, int>> candidates;
        for (int parent = 1; parent < farm; ++parent) {
            for (int d = 0; d < 4; ++d) {
                if (usedDir[parent][d]) continue;
                Point next = {pos[parent].x + delta[d].first, pos[parent].y + delta[d].second};
                if (farmAt.count(next)) continue;
                candidates.push_back({parent, d});
            }
        }

        ensuref(!candidates.empty(), "no available grid attachment");
        auto [parent, d] = rnd.any(candidates);
        Point next = {pos[parent].x + delta[d].first, pos[parent].y + delta[d].second};

        pos[farm] = next;
        farmAt[next] = farm;
        usedDir[parent][d] = 1;
        usedDir[farm][d ^ 2] = 1;
        edges.push_back({parent, farm, step, dirs[d]});
    }

    vector<int> edgeOrder(edges.size());
    for (int i = 0; i < (int)edgeOrder.size(); ++i) {
        edgeOrder[i] = i;
    }
    shuffle(edgeOrder.begin(), edgeOrder.end());

    println(n, n - 1);
    for (int index : edgeOrder) {
        const Edge& edge = edges[index];
        if (rnd.next(2) == 0) {
            println(edge.u, edge.v, edge.len, edge.dir);
        } else {
            println(edge.v, edge.u, edge.len, dirs[(dirs.find(edge.dir) + 2) % 4]);
        }
    }

    int k = rnd.next(1, min(40, n * 3));
    println(k);
    for (int i = 0; i < k; ++i) {
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        int after = rnd.next(1, n - 1);
        println(u, v, after);
    }

    return 0;
}
