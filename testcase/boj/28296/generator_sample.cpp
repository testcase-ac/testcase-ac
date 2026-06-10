#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 16);
    int k = rnd.next(1, n / 2);

    vector<int> companies;
    companies.reserve(n);
    for (int company = 1; company <= k; ++company) {
        companies.push_back(company);
        companies.push_back(company);
    }
    while ((int)companies.size() < n) {
        companies.push_back(rnd.next(1, k));
    }
    shuffle(companies.begin(), companies.end());

    vector<tuple<int, int, int>> edges;
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    int weightMode = rnd.next(0, 3);
    auto nextWeight = [&]() {
        if (weightMode == 0) {
            return rnd.next(1, 9);
        }
        if (weightMode == 1) {
            return rnd.next(1, 1000);
        }
        if (weightMode == 2) {
            return rnd.any(vector<int>{1, 2, 3, 10, 100, 1000000000});
        }
        return rnd.next(999999900, 1000000000);
    };

    for (int i = 1; i < n; ++i) {
        int parent = order[rnd.next(0, i - 1)];
        edges.emplace_back(parent, order[i], nextWeight());
    }

    vector<pair<int, int>> pairs;
    for (int x = 1; x <= n; ++x) {
        for (int y = x + 1; y <= n; ++y) {
            pairs.emplace_back(x, y);
        }
    }
    shuffle(pairs.begin(), pairs.end());

    int simpleExtra = rnd.next(0, min<int>((int)pairs.size(), 2 * n));
    for (int i = 0; i < simpleExtra; ++i) {
        edges.emplace_back(pairs[i].first, pairs[i].second, nextWeight());
    }

    int parallelExtra = rnd.next(0, min(12, n));
    for (int i = 0; i < parallelExtra; ++i) {
        auto [x, y, ignored] = rnd.any(edges);
        edges.emplace_back(x, y, nextWeight());
    }

    shuffle(edges.begin(), edges.end());

    println(n, k, (int)edges.size());
    println(companies);
    for (auto [x, y, w] : edges) {
        if (rnd.next(0, 1)) {
            swap(x, y);
        }
        println(x, y, w);
    }

    return 0;
}
