#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    set<pair<int, int>> used;
    vector<pair<int, int>> edges;

    auto addEdge = [&](int a, int b) {
        if (a == b) return;
        a = label[a];
        b = label[b];
        pair<int, int> edge = minmax(a, b);
        if (used.insert(edge).second) edges.push_back({a, b});
    };

    if (mode == 0) {
        // Tree: already connected and acyclic.
        for (int v = 2; v <= n; ++v) addEdge(v, rnd.next(1, v - 1));
    } else if (mode == 1) {
        // Forest with several components.
        int components = rnd.next(2, min(n, 5));
        for (int v = components + 1; v <= n; ++v) addEdge(v, rnd.next(1, v - 1));
    } else if (mode == 2) {
        // One connected component with surplus cycle edges.
        for (int v = 2; v <= n; ++v) addEdge(v, rnd.next(1, v - 1));
        int extra = rnd.next(1, min(10, n * (n - 1) / 2 - (n - 1)));
        for (int tries = 0; tries < 200 && extra > 0; ++tries) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            int before = edges.size();
            addEdge(a, b);
            if ((int)edges.size() > before) --extra;
        }
    } else if (mode == 3) {
        // Dense but still compact graph.
        vector<pair<int, int>> all;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) all.push_back({i, j});
        }
        shuffle(all.begin(), all.end());
        int m = rnd.next(n - 1, min<int>(all.size(), n + 12));
        for (int i = 0; i < m; ++i) addEdge(all[i].first, all[i].second);
    } else if (mode == 4) {
        // Path plus chords catches solutions that only count components.
        for (int v = 1; v < n; ++v) addEdge(v, v + 1);
        for (int v = 1; v + 2 <= n; ++v) {
            if (rnd.next(0, 1)) addEdge(v, v + 2);
        }
    } else {
        // Star-like hub with optional edges among leaves.
        int hub = rnd.next(1, n);
        int spokes = rnd.next(1, n - 1);
        vector<int> leaves;
        for (int v = 1; v <= n; ++v) {
            if (v != hub) leaves.push_back(v);
        }
        shuffle(leaves.begin(), leaves.end());
        for (int i = 0; i < spokes; ++i) addEdge(hub, leaves[i]);
        for (int i = 0; i + 1 < (int)leaves.size(); ++i) {
            if (rnd.next(0, 3) == 0) addEdge(leaves[i], leaves[i + 1]);
        }
    }

    if (edges.empty()) addEdge(1, 2);
    shuffle(edges.begin(), edges.end());

    println(n, (int)edges.size());
    for (auto [u, v] : edges) println(u, v);

    return 0;
}
