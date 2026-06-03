#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

static void addEdge(set<pair<int, int>>& edges, int a, int b) {
    if (a > b) swap(a, b);
    edges.insert({a, b});
}

static void addRandomChords(set<pair<int, int>>& edges, int n, int target) {
    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!edges.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());
    while ((int)edges.size() < target && !candidates.empty()) {
        edges.insert(candidates.back());
        candidates.pop_back();
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 2;
    set<pair<int, int>> edges;

    if (mode == 0) {
        n = rnd.next(2, 16);
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1);
        addRandomChords(edges, n, rnd.next(n - 1, min(n * (n - 1) / 2, n + 4)));
    } else if (mode == 1) {
        int layers = rnd.next(2, 6);
        n = 2 * layers + 1;
        addEdge(edges, 1, 2);
        addEdge(edges, 1, 3);
        for (int layer = 1; layer < layers; ++layer) {
            int a = 2 * layer;
            int b = 2 * layer + 1;
            int c = 2 * layer + 2;
            int d = 2 * layer + 3;
            addEdge(edges, a, c);
            addEdge(edges, a, d);
            addEdge(edges, b, c);
            addEdge(edges, b, d);
        }
        int sink = n;
        addEdge(edges, sink - 2, sink);
        addEdge(edges, sink - 1, sink);
        addRandomChords(edges, n, (int)edges.size() + rnd.next(0, layers));
    } else if (mode == 2) {
        n = rnd.next(4, 18);
        for (int v = 2; v <= n; ++v) addEdge(edges, v, rnd.next(1, v - 1));
        addRandomChords(edges, n, rnd.next(n - 1, min(n * (n - 1) / 2, 2 * n)));
    } else if (mode == 3) {
        n = rnd.next(4, 13);
        for (int i = 1; i < n; ++i) addEdge(edges, i, i + 1);
        int target = rnd.next(max(n - 1, n * (n - 1) / 3), n * (n - 1) / 2);
        addRandomChords(edges, n, target);
    } else {
        int branches = rnd.next(2, 5);
        int length = rnd.next(2, 5);
        n = 2 + branches * (length - 1);
        int nextNode = 2;
        for (int branch = 0; branch < branches; ++branch) {
            int prev = 1;
            for (int step = 1; step <= length; ++step) {
                int cur = (step == length) ? n : nextNode++;
                addEdge(edges, prev, cur);
                prev = cur;
            }
        }
        addRandomChords(edges, n, (int)edges.size() + rnd.next(0, branches));
    }

    vector<int> perm(n + 1);
    for (int i = 1; i <= n; ++i) perm[i] = i;
    if (n > 2 && rnd.next(0, 1)) {
        vector<int> middle;
        for (int i = 2; i < n; ++i) middle.push_back(i);
        shuffle(middle.begin(), middle.end());
        for (int i = 2; i < n; ++i) perm[i] = middle[i - 2];
    }

    vector<pair<int, int>> output;
    for (auto [a, b] : edges) output.push_back({perm[a], perm[b]});
    shuffle(output.begin(), output.end());

    println(n, (int)output.size());
    for (auto [a, b] : output) println(a, b);

    return 0;
}
