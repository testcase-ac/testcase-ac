#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int randomChalk(int mode, int index, int n) {
    if (mode == 0) return rnd.next(1, 12);
    if (mode == 1) return rnd.any(vector<int>{1, 2, 3, 5, 8, 13, 21});
    if (mode == 2) return (index % 2 == 0 ? rnd.next(1, 3) : rnd.next(20, 40));
    if (mode == 3) return index;
    if (mode == 4) return n - index + 1;
    if (mode == 5) return rnd.next(999990, 1000000);
    return rnd.next(1, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(18, 35);
    } else {
        n = rnd.next(2, 18);
    }

    vector<int> a(n + 1);
    int chalkMode = rnd.next(0, 6);
    int equalValue = rnd.next(1, 1000000);
    for (int i = 1; i <= n; ++i) {
        a[i] = (chalkMode == 6 ? equalValue : randomChalk(chalkMode, i, n));
    }

    vector<pair<int, int>> edges;
    if (mode == 1) {
        for (int i = 2; i <= n; ++i) edges.push_back({i - 1, i});
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) edges.push_back({1, i});
    } else if (mode == 3) {
        int pathLen = max(2, n / 2);
        for (int i = 2; i <= pathLen; ++i) edges.push_back({i - 1, i});
        for (int i = pathLen + 1; i <= n; ++i) edges.push_back({rnd.next(1, pathLen), i});
    } else if (mode == 4) {
        for (int i = 2; i <= n; ++i) edges.push_back({i / 2, i});
    } else {
        for (int i = 2; i <= n; ++i) edges.push_back({rnd.next(1, i - 1), i});
    }

    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1)) swap(edge.first, edge.second);
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
    for (auto edge : edges) println(edge.first, edge.second);

    return 0;
}
