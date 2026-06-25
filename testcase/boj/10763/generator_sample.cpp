#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 12);
    int e = rnd.any(vector<int>{1, 2, 3, 10, 1000, 1000000});
    set<pair<int, int>> edges;

    auto addEdge = [&](int a, int b) {
        if (a == b) return;
        if (a > b) swap(a, b);
        edges.insert({a, b});
    };

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        for (int i = 1; i < n; ++i) addEdge(i, i + 1);
    } else if (mode == 2) {
        n = rnd.next(3, 11);
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) addEdge(center, i);
    } else if (mode == 3) {
        n = rnd.next(4, 12);
        for (int i = 1; i <= n; ++i) addEdge(i, i % n + 1);
    } else if (mode == 4) {
        n = rnd.next(5, 13);
        for (int i = 2; i <= n; ++i) addEdge(i, rnd.next(1, i - 1));
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) addEdge(rnd.next(1, n), rnd.next(1, n));
    } else {
        n = rnd.next(3, 14);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (rnd.next(0, 99) < 22) addEdge(i, j);
            }
        }
    }

    vector<vector<int>> adj(n + 1);
    for (auto [a, b] : edges) {
        if ((int)adj[a].size() == 10 || (int)adj[b].size() == 10) continue;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> qualities;
    int qualityMode = rnd.next(0, 3);
    if (qualityMode == 0) {
        int start = rnd.next(1, 1000000 - n + 1);
        for (int i = 0; i < n; ++i) qualities.push_back(start + i);
    } else if (qualityMode == 1) {
        int step = rnd.next(2, 50);
        int start = rnd.next(1, 1000000 - step * (n - 1));
        for (int i = 0; i < n; ++i) qualities.push_back(start + i * step);
    } else if (qualityMode == 2) {
        qualities.push_back(1);
        if (n > 1) qualities.push_back(1000000);
        set<int> used(qualities.begin(), qualities.end());
        while ((int)qualities.size() < n) {
            int q = rnd.next(2, 999999);
            if (used.insert(q).second) qualities.push_back(q);
        }
    } else {
        set<int> used;
        while ((int)qualities.size() < n) {
            int q = rnd.next(1, 1000000);
            if (used.insert(q).second) qualities.push_back(q);
        }
    }
    shuffle(qualities.begin(), qualities.end());

    println(n, e);
    for (int i = 1; i <= n; ++i) {
        shuffle(adj[i].begin(), adj[i].end());
        printf("%d %d", qualities[i - 1], (int)adj[i].size());
        for (int neighbor : adj[i]) printf(" %d", neighbor);
        printf("\n");
    }

    return 0;
}
