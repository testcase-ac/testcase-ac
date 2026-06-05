#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = (mode == 0 ? rnd.next(1, 8) : rnd.next(2, 15));

    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());

    vector<vector<int>> comps;
    int at = 0;
    while (at < n) {
        int remaining = n - at;
        int maxSize = min(remaining, mode == 1 ? 3 : 6);
        int sz = (mode == 0 ? 1 : rnd.next(1, maxSize));
        vector<int> comp;
        for (int i = 0; i < sz; ++i) comp.push_back(nodes[at++]);
        comps.push_back(comp);
    }

    vector<int> water(n + 1);
    for (const auto& comp : comps) {
        int sz = (int)comp.size();
        int clean;
        int balanceMode = rnd.next(0, 3);
        if (balanceMode == 0) {
            clean = rnd.next((sz + 2) / 2, sz);
        } else if (balanceMode == 1) {
            clean = rnd.next(0, sz / 2);
        } else if (sz % 2 == 0) {
            clean = sz / 2;
        } else {
            clean = rnd.next(0, 1) ? (sz + 1) / 2 : sz / 2;
        }

        vector<int> labels(sz, 0);
        fill(labels.begin(), labels.begin() + clean, 1);
        shuffle(labels.begin(), labels.end());
        for (int i = 0; i < sz; ++i) water[comp[i]] = labels[i];
    }

    vector<pair<int, int>> edges;
    for (const auto& comp : comps) {
        int sz = (int)comp.size();
        if (sz == 1) continue;

        vector<pair<int, int>> possible;
        for (int i = 0; i < sz; ++i) {
            for (int j = i + 1; j < sz; ++j) {
                possible.emplace_back(comp[i], comp[j]);
            }
        }
        shuffle(possible.begin(), possible.end());

        if (mode == 2 || mode == 4) {
            for (int i = 1; i < sz; ++i) {
                int parent = rnd.next(0, i - 1);
                edges.emplace_back(comp[i], comp[parent]);
            }
        }

        int extraLimit = (int)possible.size();
        int extra = 0;
        if (mode == 3) {
            extra = rnd.next(extraLimit / 2, extraLimit);
        } else if (mode != 0) {
            extra = rnd.next(0, extraLimit);
        }
        for (int i = 0; i < extra; ++i) edges.push_back(possible[i]);

        if (mode == 4 && !possible.empty()) {
            int duplicates = rnd.next(1, min(4, (int)possible.size()));
            for (int i = 0; i < duplicates; ++i) edges.push_back(possible[rnd.next(0, (int)possible.size() - 1)]);
        }
    }

    shuffle(edges.begin(), edges.end());
    int q = rnd.next(1, min(20, n + 8));
    vector<int> queries;
    for (const auto& comp : comps) queries.push_back(comp[0]);
    while ((int)queries.size() < q) queries.push_back(rnd.next(1, n));
    shuffle(queries.begin(), queries.end());
    queries.resize(q);

    println(n, (int)edges.size(), q);
    vector<int> waterLine;
    for (int i = 1; i <= n; ++i) waterLine.push_back(water[i]);
    println(waterLine);
    for (auto [u, v] : edges) println(u, v);
    for (int k : queries) println(k);

    return 0;
}
