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

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 18);
    vector<int> color(n + 1, 0);
    set<pair<int, int>> edges;

    if (mode <= 2) {
        vector<int> cuts = {1, 2};
        if (n > 3) {
            cuts[0] = rnd.next(1, n - 2);
            cuts[1] = rnd.next(cuts[0] + 1, n - 1);
        }

        vector<int> vertices;
        for (int i = 1; i <= n; ++i) vertices.push_back(i);
        shuffle(vertices.begin(), vertices.end());

        for (int i = 0; i < n; ++i) {
            int group = 3;
            if (i < cuts[0]) group = 1;
            else if (i < cuts[1]) group = 2;
            color[vertices[i]] = group;
        }

        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                if (color[a] != color[b]) addEdge(edges, a, b);
            }
        }

        if (mode == 1 && !edges.empty()) {
            auto it = edges.begin();
            advance(it, rnd.next((int)edges.size()));
            edges.erase(it);
        } else if (mode == 2) {
            vector<pair<int, int>> sameGroupPairs;
            for (int a = 1; a <= n; ++a) {
                for (int b = a + 1; b <= n; ++b) {
                    if (color[a] == color[b]) sameGroupPairs.push_back({a, b});
                }
            }
            if (!sameGroupPairs.empty()) {
                pair<int, int> edge = rnd.any(sameGroupPairs);
                addEdge(edges, edge.first, edge.second);
            }
        }
    } else if (mode == 3) {
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) addEdge(edges, a, b);
        }
    } else if (mode == 4) {
        double probability = rnd.next(0.0, 0.45);
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                if (rnd.next() < probability) addEdge(edges, a, b);
            }
        }
    } else {
        int left = rnd.next(1, n - 1);
        for (int a = 1; a <= left; ++a) {
            for (int b = left + 1; b <= n; ++b) addEdge(edges, a, b);
        }
    }

    println(n, (int)edges.size());
    for (auto [a, b] : edges) println(a, b);

    return 0;
}
