#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = 2;
    string labels;
    set<pair<int, int>> edgeSet;

    auto addEdge = [&](int u, int v) {
        if (u == v) return;
        if (u > v) swap(u, v);
        edgeSet.insert({u, v});
    };

    auto randomLabel = [&]() {
        static const string alphabet = "KDH";
        return alphabet[rnd.next(3)];
    };

    if (mode == 0) {
        n = rnd.next(2, 6);
        labels.resize(n);
        for (char& c : labels) c = randomLabel();
        addEdge(rnd.next(1, n), rnd.next(1, n));
        while (edgeSet.empty()) addEdge(rnd.next(1, n), rnd.next(1, n));
    } else if (mode == 1) {
        n = rnd.next(3, 18);
        labels.resize(n);
        for (int i = 0; i < n; ++i) labels[i] = "KDH"[i % 3];
        for (int i = 1; i < n; ++i) addEdge(i, i + 1);

        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) addEdge(rnd.next(1, n), rnd.next(1, n));
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        labels = "KDH";
        while (static_cast<int>(labels.size()) < n) labels += randomLabel();
        addEdge(1, 2);
        addEdge(2, 3);
        addEdge(3, 1);

        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) addEdge(rnd.next(1, n), rnd.next(1, n));
    } else if (mode == 3) {
        int layers = rnd.next(2, 5);
        vector<vector<int>> byLayer(layers);
        labels.clear();
        for (int layer = 0; layer < layers; ++layer) {
            int width = rnd.next(1, 4);
            for (int j = 0; j < width; ++j) {
                byLayer[layer].push_back(static_cast<int>(labels.size()) + 1);
                labels += "KDH"[layer % 3];
            }
        }
        n = static_cast<int>(labels.size());

        for (int layer = 0; layer + 1 < layers; ++layer) {
            for (int u : byLayer[layer]) {
                for (int v : byLayer[layer + 1]) {
                    if (rnd.next(2)) addEdge(u, v);
                }
            }
            addEdge(rnd.any(byLayer[layer]), rnd.any(byLayer[layer + 1]));
        }

        int noise = rnd.next(0, n);
        for (int i = 0; i < noise; ++i) addEdge(rnd.next(1, n), rnd.next(1, n));
    } else {
        n = rnd.next(6, 20);
        labels.resize(n);
        for (char& c : labels) c = randomLabel();

        vector<pair<int, int>> candidates;
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                candidates.push_back({u, v});
            }
        }
        shuffle(candidates.begin(), candidates.end());

        int m = rnd.next(n - 1, min<int>(static_cast<int>(candidates.size()), 3 * n));
        for (int i = 0; i < m; ++i) addEdge(candidates[i].first, candidates[i].second);
    }

    if (edgeSet.empty()) addEdge(1, 2);

    println(n, static_cast<int>(edgeSet.size()));
    println(labels);
    for (auto [u, v] : edgeSet) println(u, v);

    return 0;
}
