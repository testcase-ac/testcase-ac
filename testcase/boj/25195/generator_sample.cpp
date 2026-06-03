#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    vector<pair<int, int>> edges;
    set<pair<int, int>> used;
    set<int> fans;

    auto addEdge = [&](int u, int v) {
        if (u != v && used.insert({u, v}).second) {
            edges.push_back({u, v});
        }
    };

    if (mode == 0) {
        n = rnd.next(2, 8);
        int len = rnd.next(2, n);
        for (int i = 1; i < len; ++i) {
            addEdge(i, i + 1);
        }
        fans.insert(1);
        for (int i = 2; i <= n; ++i) {
            if (rnd.next(0, 3) == 0) fans.insert(i);
        }
    } else if (mode == 1) {
        n = rnd.next(4, 10);
        addEdge(1, 2);
        addEdge(1, 3);
        addEdge(2, 4);
        addEdge(3, 4);
        for (int v = 5; v <= n; ++v) {
            addEdge(rnd.next(1, v - 1), v);
        }
        fans.insert(2);
        if (rnd.next(0, 1)) fans.insert(4);
    } else if (mode == 2) {
        n = rnd.next(4, 12);
        int u = rnd.next(2, n);
        int v = rnd.next(1, u - 1);
        addEdge(u, v);
        fans.insert(v);
        int extraFans = rnd.next(1, min(n, 5));
        while ((int)fans.size() < extraFans) {
            fans.insert(rnd.next(1, n));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 14);
        for (int i = 1; i < n; ++i) {
            addEdge(i, i + 1);
            if (i + 2 <= n && rnd.next(0, 2) == 0) addEdge(i, i + 2);
        }
        int fanStart = rnd.next(2, n);
        for (int v = fanStart; v <= n; ++v) {
            if (rnd.next(0, 1)) fans.insert(v);
        }
        if (fans.empty()) fans.insert(n);
    } else {
        n = rnd.next(3, 14);
        double density = rnd.next(0.15, 0.55);
        for (int u = 1; u <= n; ++u) {
            for (int v = u + 1; v <= n; ++v) {
                if (rnd.next() < density) addEdge(u, v);
            }
        }
        if (edges.empty()) addEdge(rnd.next(1, n - 1), rnd.next(2, n));

        int fanCount = rnd.next(1, min(n, 6));
        while ((int)fans.size() < fanCount) {
            fans.insert(rnd.next(1, n));
        }
    }

    if (edges.empty()) {
        addEdge(1, 2);
    }
    if (fans.empty()) {
        fans.insert(rnd.next(1, n));
    }

    shuffle(edges.begin(), edges.end());
    vector<int> fanList(fans.begin(), fans.end());
    shuffle(fanList.begin(), fanList.end());

    println(n, (int)edges.size());
    for (auto [u, v] : edges) {
        println(u, v);
    }
    println((int)fanList.size());
    println(fanList);

    return 0;
}
