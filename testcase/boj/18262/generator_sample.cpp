#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

using Edge = tuple<int, int, int, int>;

int randomCost(int profile) {
    if (profile == 0) return rnd.next(1, 12);
    if (profile == 1) return rnd.next(1, 1000);
    return rnd.wnext(1000, -2) + 1;
}

int randomFlow(int profile) {
    if (profile == 0) return rnd.next(1, 12);
    if (profile == 1) return rnd.next(1, 1000);
    return rnd.wnext(1000, 2) + 1;
}

void addEdge(vector<Edge>& edges, int a, int b, int c, int f) {
    if (rnd.next(2)) swap(a, b);
    edges.emplace_back(a, b, c, f);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = rnd.next(2, mode == 3 ? 14 : 10);
    vector<Edge> edges;

    if (mode == 0) {
        n = rnd.next(2, 8);
        int costProfile = rnd.next(3);
        int flowProfile = rnd.next(3);
        for (int v = 1; v < n; ++v) {
            addEdge(edges, v, v + 1, randomCost(costProfile), randomFlow(flowProfile));
        }
    } else if (mode == 1) {
        n = rnd.next(4, 10);
        int branches = rnd.next(2, min(5, n - 2));
        vector<int> middle;
        for (int v = 2; v < n; ++v) middle.push_back(v);
        shuffle(middle.begin(), middle.end());

        for (int i = 0; i < branches; ++i) {
            int mid = middle[i];
            int cheap = rnd.next(1, 20);
            int expensive = rnd.next(50, 1000);
            int lowFlow = rnd.next(1, 40);
            int highFlow = rnd.next(200, 1000);
            if (rnd.next(2)) {
                addEdge(edges, 1, mid, cheap, lowFlow);
                addEdge(edges, mid, n, expensive, highFlow);
            } else {
                addEdge(edges, 1, mid, expensive, highFlow);
                addEdge(edges, mid, n, cheap, lowFlow);
            }
        }
    } else {
        int costProfile = rnd.next(3);
        int flowProfile = rnd.next(3);
        vector<pair<int, int>> candidates;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                candidates.emplace_back(i, j);
            }
        }

        for (int v = 1; v < n; ++v) {
            addEdge(edges, v, v + 1, randomCost(costProfile), randomFlow(flowProfile));
        }

        shuffle(candidates.begin(), candidates.end());
        int targetEdges = rnd.next(n - 1, mode == 2 ? min(2 * n, 1000) : min<int>(candidates.size(), 1000));
        for (auto [a, b] : candidates) {
            if ((a + 1 == b) || static_cast<int>(edges.size()) >= targetEdges) continue;
            addEdge(edges, a, b, randomCost(costProfile), randomFlow(flowProfile));
        }
    }

    shuffle(edges.begin(), edges.end());
    println(n, static_cast<int>(edges.size()));
    for (auto [a, b, c, f] : edges) {
        println(a, b, c, f);
    }

    return 0;
}
