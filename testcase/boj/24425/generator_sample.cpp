#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int a;
    int b;
    int color;
};

void addEdge(vector<Edge>& edges, set<pair<int, int>>& used, int a, int b, int color) {
    if (a > b) {
        swap(a, b);
    }
    if (used.insert({a, b}).second) {
        edges.push_back({a, b, color});
    }
}

int randomColor(int mode) {
    if (mode == 1) {
        return 1;
    }
    if (mode == 2) {
        return 2;
    }
    return rnd.next(1, 2);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    vector<Edge> edges;
    set<pair<int, int>> used;

    if (mode == 0) {
        n = rnd.next(2, 14);
        for (int i = 1; i < n; ++i) {
            addEdge(edges, used, i, i + 1, randomColor(0));
        }
    } else if (mode == 1) {
        n = rnd.next(3, 16);
        int hub = rnd.next(1, n);
        for (int town = 1; town <= n; ++town) {
            if (town != hub) {
                addEdge(edges, used, hub, town, randomColor(0));
            }
        }
    } else {
        for (int town = 2; town <= n; ++town) {
            addEdge(edges, used, town, rnd.next(1, town - 1), randomColor(mode == 3 ? 1 : 0));
        }
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) {
                candidates.push_back({a, b});
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int extraLimit = static_cast<int>(candidates.size());
    int extra = 0;
    if (mode == 2) {
        extra = rnd.next(0, min(extraLimit, n));
    } else if (mode == 3) {
        extra = rnd.next(0, min(extraLimit, 2 * n));
    } else if (mode == 4) {
        extra = rnd.next(extraLimit / 2, extraLimit);
    } else {
        extra = rnd.next(0, min(extraLimit, 4));
    }

    for (int i = 0; i < extra; ++i) {
        addEdge(edges, used, candidates[i].first, candidates[i].second, randomColor(mode == 4 ? 0 : 2));
    }

    shuffle(edges.begin(), edges.end());

    int q = rnd.next(1, min(8, n - 1));
    vector<int> targets;
    for (int i = 0; i < q; ++i) {
        if (i == 0 && rnd.next(0, 3) == 0) {
            targets.push_back(n);
        } else {
            targets.push_back(rnd.next(2, n));
        }
    }

    vector<int> lChoices = {1, 2, 3, 5, 10, 25, 100, 1000000000};
    int l = rnd.any(lChoices);

    println(n, static_cast<int>(edges.size()), q, l);
    for (const Edge& edge : edges) {
        println(edge.a, edge.b, edge.color);
    }
    for (int target : targets) {
        println(target);
    }

    return 0;
}
