#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = 2;
    if (mode == 0) {
        n = rnd.next(2, 6);
    } else if (mode == 1) {
        n = rnd.next(4, 12);
    } else if (mode == 2) {
        n = rnd.next(6, 18);
    } else {
        n = rnd.next(8, 30);
    }

    vector<pair<int, int>> edges;
    if (mode == 0) {
        int center = rnd.next(1, n);
        for (int cow = 1; cow <= n; ++cow) {
            if (cow != center) edges.push_back({center, cow});
        }
    } else if (mode == 1) {
        for (int cow = 1; cow < n; ++cow) {
            edges.push_back({cow, cow + 1});
        }
    } else if (mode == 2) {
        int block = rnd.next(2, 5);
        for (int first = 1; first <= n; first += block) {
            int last = min(n, first + block - 1);
            for (int cow = first; cow < last; ++cow) {
                edges.push_back({cow, cow + 1});
            }
        }
    } else {
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                candidates.push_back({a, b});
            }
        }
        shuffle(candidates.begin(), candidates.end());

        int maxEdges = min(2000, int(candidates.size()));
        int m = 1;
        if (mode == 3) {
            m = rnd.next(1, min(maxEdges, max(1, n + rnd.next(0, n))));
        } else {
            m = rnd.next(max(1, maxEdges / 3), maxEdges);
        }
        edges.assign(candidates.begin(), candidates.begin() + m);
    }

    shuffle(edges.begin(), edges.end());
    if (edges.empty()) edges.push_back({1, 2});
    if (int(edges.size()) > 2000) edges.resize(2000);

    int q = rnd.next(1, 100);
    vector<pair<int, int>> queries;
    queries.reserve(q);

    for (int i = 0; i < q; ++i) {
        if (i < int(edges.size()) && rnd.next(3) == 0) {
            queries.push_back(edges[i]);
        } else {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n - 1);
            if (y >= x) ++y;
            queries.push_back({x, y});
        }
    }

    println(n, int(edges.size()), q);
    for (auto [a, b] : edges) println(a, b);
    for (auto [x, y] : queries) println(x, y);

    return 0;
}
