#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 14);
    vector<int> degree(n + 1);
    vector<pair<int, int>> edges;

    auto addEdge = [&](int a, int b) {
        if (a == b || degree[a] >= 3 || degree[b] >= 3) return false;
        ++degree[a];
        ++degree[b];
        edges.emplace_back(a, b);
        return true;
    };

    if (mode == 0) {
        int center = rnd.next(1, n);
        vector<int> leaves;
        for (int i = 1; i <= n; ++i) {
            if (i != center) leaves.push_back(i);
        }
        shuffle(leaves.begin(), leaves.end());
        int cnt = rnd.next(1, min(3, (int)leaves.size()));
        for (int i = 0; i < cnt; ++i) addEdge(center, leaves[i]);
    } else if (mode == 1) {
        vector<int> p(n);
        for (int i = 0; i < n; ++i) p[i] = i + 1;
        shuffle(p.begin(), p.end());
        int len = rnd.next(2, n);
        for (int i = 1; i < len; ++i) addEdge(p[i - 1], p[i]);
        if (len >= 4 && rnd.next(0, 1)) addEdge(p[len - 1], p[0]);
    } else if (mode == 2) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n - 1);
        if (b >= a) ++b;
        int copies = rnd.next(1, 3);
        for (int i = 0; i < copies; ++i) addEdge(a, b);
    } else {
        vector<pair<int, int>> candidates;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                int copies = mode == 3 ? rnd.next(1, 2) : rnd.next(1, 3);
                for (int k = 0; k < copies; ++k) candidates.emplace_back(i, j);
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int target = rnd.next(1, min(18, 3 * n / 2));
        for (auto [a, b] : candidates) {
            if ((int)edges.size() >= target) break;
            addEdge(a, b);
        }
    }

    while (edges.empty()) {
        int a = rnd.next(1, n);
        int b = rnd.next(1, n - 1);
        if (b >= a) ++b;
        addEdge(a, b);
    }

    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (auto [a, b] : edges) {
        if (rnd.next(0, 1)) swap(a, b);
        println(a, b);
    }

    return 0;
}
