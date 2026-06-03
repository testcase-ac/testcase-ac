#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using Edge = tuple<int, int, int>;

void addEdge(vector<Edge>& edges, set<pair<int, int>>& seen, int x, int y, int z) {
    if (x > y) swap(x, y);
    if (x == y || !seen.insert({x, y}).second) return;
    edges.emplace_back(x, y, z);
}

vector<pair<int, int>> candidateEdges(int m) {
    vector<pair<int, int>> candidates;
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            candidates.emplace_back(i, j);
        }
    }
    shuffle(candidates.begin(), candidates.end());
    return candidates;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(2, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int m = rnd.next(5, 14);
        int mode = rnd.next(4);

        vector<Edge> edges;
        set<pair<int, int>> seen;

        if (mode == 0) {
            int target = rnd.next(1, min(20, m * (m - 1) / 2));
            for (auto [x, y] : candidateEdges(m)) {
                if (x == m - 1 || y == m - 1) continue;
                addEdge(edges, seen, x, y, rnd.next(1, 4));
                if ((int)edges.size() == target) break;
            }
        } else if (mode == 1) {
            int via = rnd.next(1, m - 2);
            addEdge(edges, seen, 0, m - 1, 4);
            addEdge(edges, seen, 0, via, 1);
            addEdge(edges, seen, via, m - 1, 1);
        } else if (mode == 2) {
            vector<int> order;
            for (int i = 0; i < m; ++i) order.push_back(i);
            shuffle(order.begin() + 1, order.end() - 1);
            for (int i = 0; i + 1 < m; ++i) {
                addEdge(edges, seen, order[i], order[i + 1], rnd.next(1, 4));
            }
        } else {
            int target = rnd.next(m - 1, min(20, m * (m - 1) / 2));
            for (int i = 1; i < m; ++i) {
                addEdge(edges, seen, i, rnd.next(0, i - 1), rnd.next(1, 4));
            }
            for (auto [x, y] : candidateEdges(m)) {
                addEdge(edges, seen, x, y, rnd.next(1, 4));
                if ((int)edges.size() == target) break;
            }
        }

        if (rnd.next(2)) {
            for (auto& [x, y, z] : edges) {
                if (rnd.next(2)) swap(x, y);
            }
        }
        shuffle(edges.begin(), edges.end());
        if ((int)edges.size() > 20) edges.resize(20);

        println((int)edges.size(), m);
        for (auto [x, y, z] : edges) {
            println(x, y, z);
        }
    }

    return 0;
}
