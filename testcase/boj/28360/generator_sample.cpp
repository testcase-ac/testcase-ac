#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

void addEdge(set<pair<int, int>>& edges, int v, int w) {
    if (v < w && static_cast<int>(edges.size()) < 100) {
        edges.insert({v, w});
    }
}

void addRandomForwardEdges(set<pair<int, int>>& edges, int n, int target) {
    vector<pair<int, int>> candidates;
    for (int v = 1; v <= n; ++v) {
        for (int w = v + 1; w <= n; ++w) {
            candidates.push_back({v, w});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    for (auto edge : candidates) {
        if (static_cast<int>(edges.size()) >= target || static_cast<int>(edges.size()) >= 100) {
            break;
        }
        edges.insert(edge);
    }
}

} // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    set<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        int len = rnd.next(2, n);
        for (int i = 1; i < len; ++i) {
            addEdge(edges, i, i + 1);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 18);
        int fan = rnd.next(2, n - 1);
        for (int w = 2; w <= fan + 1; ++w) {
            addEdge(edges, 1, w);
        }
        int sink = rnd.next(fan + 1, n);
        for (int v = 2; v <= fan + 1 && v < sink; ++v) {
            addEdge(edges, v, sink);
        }
    } else if (mode == 3) {
        n = rnd.next(6, 20);
        int a = rnd.next(2, 5);
        int b = rnd.next(a + 1, n - 1);
        for (int w = 2; w <= a; ++w) {
            addEdge(edges, 1, w);
        }
        for (int v = 2; v <= a; ++v) {
            int out = rnd.next(1, min(4, n - b));
            for (int k = 0; k < out; ++k) {
                addEdge(edges, v, rnd.next(b + 1, n));
            }
        }
        for (int v = a + 1; v <= b; ++v) {
            if (rnd.next(0, 1)) {
                addEdge(edges, v, rnd.next(v + 1, n));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(5, 22);
        int target = rnd.next(n / 2, min(100, n * (n - 1) / 6));
        addRandomForwardEdges(edges, n, target);
    } else if (mode == 5) {
        n = rnd.next(10, 24);
        int target = rnd.next(35, min(100, n * (n - 1) / 2));
        addRandomForwardEdges(edges, n, target);
    } else {
        n = rnd.next(8, 18);
        int split = rnd.next(3, n - 3);
        for (int w = 2; w <= split; ++w) {
            if (rnd.next(0, 2) > 0) {
                addEdge(edges, 1, w);
            }
        }
        for (int v = split + 1; v < n; ++v) {
            if (rnd.next(0, 1)) {
                addEdge(edges, v, rnd.next(v + 1, n));
            }
        }
        addRandomForwardEdges(edges, n, rnd.next(static_cast<int>(edges.size()), min(100, n * 2)));
    }

    vector<pair<int, int>> output(edges.begin(), edges.end());
    shuffle(output.begin(), output.end());

    println(n, static_cast<int>(output.size()));
    for (auto edge : output) {
        println(edge.first, edge.second);
    }

    return 0;
}
