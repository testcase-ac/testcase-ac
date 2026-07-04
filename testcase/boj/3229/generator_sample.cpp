#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

static void addEdge(set<pair<int, int>>& used, vector<pair<int, int>>& edges, int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    if (a == b) {
        return;
    }
    if (used.insert({a, b}).second) {
        edges.push_back({a, b});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int k = rnd.next(2, mode == 4 ? 60 : 24);

    set<pair<int, int>> used;
    vector<pair<int, int>> edges;

    if (mode == 0) {
        addEdge(used, edges, 1, k);
    } else if (mode == 1) {
        for (int floor = 1; floor < k; ++floor) {
            addEdge(used, edges, floor, floor + 1);
        }
    } else {
        vector<int> route = {1};
        int current = 1;
        while (current < k) {
            int maxStep = max(1, min(k - current, mode == 2 ? 4 : 12));
            current += rnd.next(1, maxStep);
            route.push_back(current);
        }
        for (int i = 1; i < (int)route.size(); ++i) {
            addEdge(used, edges, route[i - 1], route[i]);
        }
    }

    int extraBudget = rnd.next(0, min(3 * k, 80));
    for (int i = 0; i < extraBudget; ++i) {
        int a = rnd.next(1, k - 1);
        int span;
        if (mode == 3) {
            span = rnd.next(1, min(5, k - a));
        } else if (mode == 4) {
            span = rnd.next(max(1, (k - a) / 2), k - a);
        } else {
            span = rnd.next(1, k - a);
        }
        addEdge(used, edges, a, a + span);
    }

    shuffle(edges.begin(), edges.end());

    println(k, (int)edges.size());
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
