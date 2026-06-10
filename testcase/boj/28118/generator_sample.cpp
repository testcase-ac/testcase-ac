#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

void addEdge(set<pair<int, int>>& edges, int a, int b) {
    if (a > b) swap(a, b);
    edges.insert({a, b});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = rnd.next(3, 14);
    if (mode == 7) n = rnd.next(15, 40);

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) label[i] = i;
    shuffle(label.begin() + 1, label.end());

    set<pair<int, int>> edges;

    if (mode == 0) {
        addEdge(edges, label[1], label[2]);
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) addEdge(edges, label[i], label[i + 1]);
    } else if (mode == 2) {
        int center = label[1];
        int leaves = rnd.next(2, n - 1);
        for (int i = 2; i <= leaves + 1; ++i) addEdge(edges, center, label[i]);
    } else if (mode == 3) {
        int used = 1;
        while (used <= n) {
            int remaining = n - used + 1;
            int size = rnd.next(1, min(5, remaining));
            if (remaining <= 2) size = remaining;
            for (int i = used; i < used + size; ++i) {
                for (int j = i + 1; j < used + size; ++j) {
                    addEdge(edges, label[i], label[j]);
                }
            }
            used += size;
        }
        if (edges.empty()) addEdge(edges, label[1], label[2]);
    } else if (mode == 4) {
        double density = rnd.next(0.12, 0.42);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next() < density) addEdge(edges, label[i], label[j]);
            }
        }
        if (edges.empty()) addEdge(edges, label[1], label[2]);
    } else if (mode == 5) {
        int split = rnd.next(1, n - 1);
        for (int i = 1; i <= split; ++i) {
            for (int j = split + 1; j <= n; ++j) {
                if (rnd.next() < 0.35) addEdge(edges, label[i], label[j]);
            }
        }
        if (edges.empty()) addEdge(edges, label[1], label[n]);
    } else {
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                addEdge(edges, label[i], label[j]);
            }
        }

        vector<pair<int, int>> all(edges.begin(), edges.end());
        shuffle(all.begin(), all.end());
        int removeCount = 0;
        if (mode == 6) removeCount = rnd.next(0, min<int>(10, all.size() - 1));
        if (mode == 7) removeCount = rnd.next(max(1, n / 2), min<int>(all.size() - 1, n * 2));
        for (int i = 0; i < removeCount; ++i) edges.erase(all[i]);
    }

    vector<pair<int, int>> out(edges.begin(), edges.end());
    shuffle(out.begin(), out.end());

    println(n, int(out.size()));
    for (auto [a, b] : out) println(a, b);

    return 0;
}
