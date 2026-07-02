#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int randomHouseCount(int mode) {
    if (mode == 0) {
        static const vector<int> small = {2, 3, 4, 5, 6};
        return rnd.any(small);
    }
    if (mode == 1) return rnd.next(2, 4);
    if (mode == 2) return 2 * rnd.next(1, 8);
    if (mode == 3) return 2 * rnd.next(1, 8) + 1;
    if (mode == 4) return rnd.any(vector<int>{2, 999999999, 1000000000});
    return rnd.next(2, 30);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 18);
    int cycleSize = rnd.next(3, n);
    int houseMode = rnd.next(0, 5);

    vector<int> vertices(n);
    for (int i = 0; i < n; ++i) vertices[i] = i + 1;
    shuffle(vertices.begin(), vertices.end());

    vector<pair<int, int>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int a, int b) {
        auto edge = minmax(a, b);
        if (used.insert(edge).second) edges.push_back({a, b});
    };

    for (int i = 0; i < cycleSize; ++i) {
        addEdge(vertices[i], vertices[(i + 1) % cycleSize]);
    }

    for (int i = cycleSize; i < n; ++i) {
        int parentLimit = i;
        int parentIndex;
        int attachMode = rnd.next(0, 2);
        if (attachMode == 0) {
            parentIndex = rnd.next(0, cycleSize - 1);
        } else if (attachMode == 1) {
            parentIndex = i - 1;
        } else {
            parentIndex = rnd.next(0, parentLimit - 1);
        }
        addEdge(vertices[i], vertices[parentIndex]);
    }

    if (rnd.next(2)) shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(2)) swap(edge.first, edge.second);
    }

    println(n);
    for (const auto& edge : edges) {
        println(edge.first, edge.second, randomHouseCount(houseMode));
    }

    return 0;
}
