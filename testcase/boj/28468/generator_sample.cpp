#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 0;
    set<pair<int, int>> edges;

    auto addEdge = [&](int a, int b) {
        if (a == b) return;
        edges.insert(minmax(a, b));
    };

    if (mode == 0) {
        n = rnd.next(2, 8);
        int maxM = n * (n - 1) / 2;
        int targetM = rnd.next(1, maxM);
        vector<pair<int, int>> candidates;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                candidates.emplace_back(i, j);
            }
        }
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < targetM; ++i) {
            addEdge(candidates[i].first, candidates[i].second);
        }
    } else if (mode == 1) {
        n = rnd.next(7, 14);
        int center = rnd.next(1, n);
        vector<int> others;
        for (int v = 1; v <= n; ++v) {
            if (v != center) others.push_back(v);
        }
        shuffle(others.begin(), others.end());

        for (int v : others) addEdge(center, v);
        addEdge(others[0], others[1]);
        addEdge(others[2], others[3]);

        int extra = rnd.next(0, 8);
        while (extra--) {
            int i = rnd.next(0, (int)others.size() - 1);
            int j = rnd.next(0, (int)others.size() - 1);
            addEdge(others[i], others[j]);
        }
    } else if (mode == 2) {
        n = rnd.next(7, 12);
        int cliqueSize = rnd.next(5, n);
        vector<int> vertices(n);
        for (int i = 0; i < n; ++i) vertices[i] = i + 1;
        shuffle(vertices.begin(), vertices.end());

        for (int i = 0; i < cliqueSize; ++i) {
            for (int j = i + 1; j < cliqueSize; ++j) {
                addEdge(vertices[i], vertices[j]);
            }
        }
        for (int i = cliqueSize; i < n; ++i) {
            int links = rnd.next(1, min(4, cliqueSize));
            vector<int> clique(vertices.begin(), vertices.begin() + cliqueSize);
            shuffle(clique.begin(), clique.end());
            for (int j = 0; j < links; ++j) addEdge(vertices[i], clique[j]);
        }
    } else if (mode == 3) {
        n = rnd.next(7, 15);
        for (int v = 2; v <= n; ++v) {
            addEdge(1, v);
        }
        for (int v = 2; v < n; ++v) {
            if (rnd.next(0, 1)) addEdge(v, v + 1);
        }
        int chords = rnd.next(0, 5);
        while (chords--) {
            addEdge(rnd.next(2, n), rnd.next(2, n));
        }
    } else {
        n = rnd.next(8, 16);
        double density = rnd.next(0.25, 0.75);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < density) addEdge(i, j);
            }
        }
        if (edges.empty()) addEdge(1, 2);
    }

    vector<pair<int, int>> output(edges.begin(), edges.end());
    shuffle(output.begin(), output.end());
    for (auto& edge : output) {
        if (rnd.next(0, 1)) swap(edge.first, edge.second);
    }

    println(n, (int)output.size());
    for (auto [a, b] : output) {
        println(a, b);
    }

    return 0;
}
