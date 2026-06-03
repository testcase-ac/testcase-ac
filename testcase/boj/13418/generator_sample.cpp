#include "testlib.h"
#include <algorithm>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

struct Edge {
    int a;
    int b;
    int c;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int maxM = n * (n - 1) / 2;
    int treeEdges = n - 1;
    int extraLimit = maxM - treeEdges;
    int extraEdges = rnd.next(0, min(extraLimit, rnd.next(0, maxM / 2)));

    vector<Edge> roads;
    set<pair<int, int>> used;

    vector<int> order;
    for (int i = 1; i <= n; ++i) order.push_back(i);
    shuffle(order.begin(), order.end());

    for (int i = 1; i < n; ++i) {
        int a = order[i];
        int b = order[rnd.next(0, i - 1)];
        roads.push_back({a, b, rnd.next(0, 1)});
        used.insert(minmax(a, b));
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    double uphillBias = rnd.next(0.15, 0.85);
    for (int i = 0; i < extraEdges; ++i) {
        auto [a, b] = candidates[i];
        int c = rnd.next() < uphillBias ? 0 : 1;
        roads.push_back({a, b, c});
    }

    shuffle(roads.begin(), roads.end());
    int entranceC = rnd.next(0, 1);

    println(n, int(roads.size()));
    println(0, 1, entranceC);
    for (Edge edge : roads) {
        if (rnd.next(0, 1)) swap(edge.a, edge.b);
        println(edge.a, edge.b, edge.c);
    }

    return 0;
}
