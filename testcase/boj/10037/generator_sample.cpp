#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 14);
    vector<pair<int, int>> edges;

    auto addEdge = [&](int a, int b) {
        if (rnd.next(2)) swap(a, b);
        edges.push_back({a, b});
    };

    if (mode == 0) {
        int repeats = rnd.next(1, 8);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n - 1);
        if (b >= a) ++b;
        for (int i = 0; i < repeats; ++i) addEdge(a, b);
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) addEdge(i, i + 1);
        int extra = rnd.next(0, n);
        for (int i = 0; i < extra; ++i) {
            int a = rnd.next(1, n);
            int b = rnd.next(1, n);
            if (a == b || (a % 2) == (b % 2)) {
                --i;
                continue;
            }
            addEdge(a, b);
        }
    } else if (mode == 2) {
        int left = rnd.next(1, n - 1);
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= left; ++a) {
            for (int b = left + 1; b <= n; ++b) {
                candidates.push_back({a, b});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int m = rnd.next(1, (int)candidates.size());
        for (int i = 0; i < m; ++i) addEdge(candidates[i].first, candidates[i].second);
    } else if (mode == 3) {
        n = rnd.next(3, 13);
        if (n % 2 == 0) ++n;
        for (int i = 1; i < n; ++i) addEdge(i, i + 1);
        addEdge(n, 1);
    } else if (mode == 4) {
        n = rnd.next(4, 14);
        int split = rnd.next(2, n - 2);
        for (int i = 1; i < split; ++i) addEdge(i, i + 1);
        for (int i = split; i < n; ++i) addEdge(i, i + 1);
        int duplicateCount = rnd.next(1, 4);
        for (int i = 0; i < duplicateCount; ++i) addEdge(1, 2);
    } else {
        n = rnd.next(3, 12);
        vector<pair<int, int>> candidates;
        for (int a = 1; a <= n; ++a) {
            for (int b = a + 1; b <= n; ++b) {
                candidates.push_back({a, b});
            }
        }
        shuffle(candidates.begin(), candidates.end());
        int m = rnd.next(n, min((int)candidates.size(), 24));
        for (int i = 0; i < m; ++i) addEdge(candidates[i].first, candidates[i].second);
    }

    shuffle(edges.begin(), edges.end());
    println(n, (int)edges.size());
    for (auto edge : edges) println(edge.first, edge.second);

    return 0;
}
