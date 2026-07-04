#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int q = rnd.next(1, 12);
    int mode = rnd.next(0, 4);

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    vector<int> parent(n + 1, 0);
    for (int i = 1; i < n; ++i) {
        if (mode == 0) {
            parent[i] = i - 1;
        } else if (mode == 1) {
            parent[i] = 0;
        } else if (mode == 2) {
            parent[i] = (i - 1) / 2;
        } else {
            parent[i] = rnd.next(0, i - 1);
        }
    }

    int maxBase = rnd.next(1, 30);
    vector<int> weights;
    for (int i = 1; i < n; ++i) {
        int w;
        if (mode == 3) {
            w = rnd.next(1, maxBase);
        } else if (mode == 4) {
            w = rnd.any(vector<int>{1, maxBase, rnd.next(1, maxBase)});
        } else {
            w = rnd.next(1, maxBase);
        }
        weights.push_back(w);
    }
    int maxWeight = *max_element(weights.begin(), weights.end());

    vector<pair<int, int>> queries;
    queries.push_back({1, maxWeight});
    while ((int)queries.size() < q) {
        int queryMode = rnd.next(0, 4);
        int l;
        int r;
        if (queryMode == 0) {
            l = rnd.next(1, maxWeight);
            r = rnd.next(l, maxWeight);
        } else if (queryMode == 1) {
            l = maxWeight + rnd.next(1, 5);
            r = l + rnd.next(0, 10);
        } else if (queryMode == 2) {
            l = rnd.next(1, maxWeight);
            r = rnd.next(maxWeight, maxWeight + 10);
        } else if (queryMode == 3) {
            l = r = rnd.next(1, maxWeight);
        } else {
            l = rnd.next(1, 30);
            r = rnd.next(l, 40);
        }
        queries.push_back({l, r});
    }

    println(n, q);
    for (int i = 1; i < n; ++i) {
        int u = order[i];
        int v = order[parent[i]];
        if (rnd.next(0, 1)) {
            swap(u, v);
        }
        println(u, v, weights[i - 1]);
    }
    for (auto query : queries) {
        println(query.first, query.second);
    }

    return 0;
}
