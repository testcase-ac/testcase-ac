#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 24);
    if (mode == 0) n = rnd.next(2, 8);
    if (mode == 1) n = rnd.next(10, 30);

    bool duplicateRestaurants = rnd.next(0, 5) == 0;
    int k = duplicateRestaurants ? rnd.next(n, min(1000, n + 8)) : rnd.next(1, n);

    vector<int> restaurants;
    if (duplicateRestaurants) {
        int baseCount = rnd.next(1, n);
        vector<int> base(n);
        iota(base.begin(), base.end(), 1);
        shuffle(base.begin(), base.end());
        base.resize(baseCount);
        for (int i = 0; i < k; ++i) restaurants.push_back(rnd.any(base));
    } else {
        restaurants.resize(n);
        iota(restaurants.begin(), restaurants.end(), 1);
        shuffle(restaurants.begin(), restaurants.end());
        restaurants.resize(k);
    }

    vector<pair<int, int>> edges;
    set<pair<int, int>> used;
    auto addEdge = [&](int a, int b, bool uniqueOnly) {
        if (a > b) swap(a, b);
        if (uniqueOnly && !used.insert({a, b}).second) return false;
        edges.push_back({a, b});
        return true;
    };

    if (mode == 0) {
        for (int city = 2; city <= n; ++city) addEdge(1, city, true);
    } else if (mode == 1) {
        for (int city = 1; city < n; ++city) addEdge(city, city + 1, true);
    } else {
        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n; ++i) {
            int parentIndex = mode == 2 ? rnd.next(0, i - 1) : max(0, i - rnd.next(1, min(i, 4)));
            addEdge(order[i], order[parentIndex], true);
        }
    }

    vector<pair<int, int>> candidates;
    for (int a = 1; a <= n; ++a) {
        for (int b = a + 1; b <= n; ++b) {
            if (!used.count({a, b})) candidates.push_back({a, b});
        }
    }
    shuffle(candidates.begin(), candidates.end());

    int extraUnique = candidates.empty() ? 0 : rnd.next(0, min<int>(candidates.size(), n + 8));
    for (int i = 0; i < extraUnique; ++i) addEdge(candidates[i].first, candidates[i].second, true);

    if (rnd.next(0, 3) == 0) {
        int duplicateCount = rnd.next(1, min<int>(6, edges.size()));
        for (int i = 0; i < duplicateCount; ++i) edges.push_back(rnd.any(edges));
    }

    shuffle(edges.begin(), edges.end());

    println(n, k, static_cast<int>(edges.size()));
    for (int city : restaurants) println(city);
    for (auto [a, b] : edges) {
        if (rnd.next(0, 1)) swap(a, b);
        int weightMode = rnd.next(0, 4);
        int d = 1;
        if (weightMode == 0) d = 1;
        else if (weightMode == 1) d = rnd.next(1, 9);
        else if (weightMode == 2) d = rnd.next(10, 100);
        else if (weightMode == 3) d = rnd.next(900, 1000);
        else d = rnd.next(1, 1000);
        println(a, b, d);
    }

    return 0;
}
