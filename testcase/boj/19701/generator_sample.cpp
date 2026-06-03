#include "testlib.h"

#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int v = rnd.next(2, 12);

    vector<tuple<int, int, int, int>> edges;
    set<pair<int, int>> used;

    auto addEdge = [&](int a, int b, int t, int k) {
        if (a > b) {
            swap(a, b);
        }
        if (!used.insert({a, b}).second) {
            return false;
        }
        edges.emplace_back(a, b, t, k);
        return true;
    };

    auto chooseWeight = [&]() {
        int t;
        int k;
        if (mode == 0) {
            t = rnd.next(1, 15);
            k = rnd.next(1, 20);
        } else if (mode == 1) {
            t = rnd.next(1, 30);
            k = rnd.next(1, 1000000000);
        } else if (mode == 2) {
            t = rnd.next(19960, 20000);
            k = rnd.next(1, 1000000000);
        } else if (mode == 3) {
            t = rnd.next(1, 20000);
            k = rnd.next(max(1, t - 5), t + 20);
        } else {
            t = rnd.next(1, 20000);
            k = rnd.next(1, 1000000000);
        }
        return pair<int, int>{t, k};
    };

    for (int city = 2; city <= v; ++city) {
        int parent;
        if (mode == 0) {
            parent = city - 1;
        } else if (mode == 1) {
            parent = 1;
        } else {
            parent = rnd.next(1, city - 1);
        }
        auto [t, k] = chooseWeight();
        addEdge(parent, city, t, k);
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= v; ++a) {
        for (int b = a + 1; b <= v; ++b) {
            if (!used.count({a, b})) {
                candidates.emplace_back(a, b);
            }
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int maxExtra = static_cast<int>(candidates.size());
    int extra;
    if (mode == 0) {
        extra = rnd.next(0, min(maxExtra, 2));
    } else if (mode == 1) {
        extra = rnd.next(0, min(maxExtra, v));
    } else if (mode == 2) {
        extra = rnd.next(min(maxExtra, v / 2), min(maxExtra, v + 4));
    } else {
        extra = rnd.next(0, maxExtra);
    }

    for (int i = 0; i < extra; ++i) {
        auto [a, b] = candidates[i];
        auto [t, k] = chooseWeight();
        addEdge(a, b, t, k);
    }

    shuffle(edges.begin(), edges.end());

    println(v, static_cast<int>(edges.size()));
    for (auto [x, y, t, k] : edges) {
        if (rnd.next(0, 1)) {
            swap(x, y);
        }
        println(x, y, t, k);
    }

    return 0;
}
