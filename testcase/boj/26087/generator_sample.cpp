#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 1000000;
    int mode = rnd.next(0, 6);
    int n;
    int q;
    vector<pair<int, int>> queries;

    auto addRandomInterval = [&]() {
        int l = rnd.next(1, n);
        int r = rnd.next(l, n);
        queries.push_back({l, r});
    };

    if (mode == 0) {
        n = rnd.next(1, 8);
        q = rnd.next(1, 8);
        for (int i = 0; i < q; ++i) addRandomInterval();
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        q = rnd.next(3, 20);
        for (int i = 0; i < q; ++i) {
            if (rnd.next(0, 1) == 0) {
                int p = rnd.next(1, n);
                queries.push_back({p, p});
            } else {
                addRandomInterval();
            }
        }
    } else if (mode == 2) {
        n = rnd.next(5, 60);
        q = rnd.next(4, 18);
        int center = rnd.next(1, n);
        for (int i = 0; i < q; ++i) {
            int l = rnd.next(1, center);
            int r = rnd.next(center, n);
            queries.push_back({l, r});
        }
    } else if (mode == 3) {
        n = rnd.next(10, 80);
        q = rnd.next(5, 25);
        for (int i = 0; i < q; ++i) {
            int len = rnd.next(1, min(n, 10));
            int l = rnd.next(1, n - len + 1);
            queries.push_back({l, l + len - 1});
        }
    } else if (mode == 4) {
        n = rnd.next(20, 120);
        q = rnd.next(5, 20);
        for (int i = 0; i < q; ++i) {
            int margin = min(i, n - 1);
            int l = rnd.next(1, margin + 1);
            int r = rnd.next(n - margin, n);
            if (l > r) swap(l, r);
            queries.push_back({l, r});
        }
    } else if (mode == 5) {
        n = rnd.next(MAX_N - 1000, MAX_N);
        q = rnd.next(2, 12);
        for (int i = 0; i < q; ++i) {
            int kind = rnd.next(0, 2);
            if (kind == 0) {
                int r = rnd.next(MAX_N - 1000, n);
                queries.push_back({1, r});
            } else if (kind == 1) {
                int l = rnd.next(1, 1000);
                queries.push_back({l, n});
            } else {
                addRandomInterval();
            }
        }
    } else {
        n = rnd.next(1, MAX_N);
        q = 1;
        addRandomInterval();
    }

    shuffle(queries.begin(), queries.end());

    println(n);
    println(static_cast<int>(queries.size()));
    for (auto [l, r] : queries) println(l, r);

    return 0;
}
