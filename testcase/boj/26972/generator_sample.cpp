#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 8);
    } else {
        n = rnd.next(4, 15);
    }

    vector<pair<int, int>> edges;
    if (mode == 1) {
        for (int i = 2; i <= n; ++i) edges.push_back({i - 1, i});
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) edges.push_back({1, i});
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) edges.push_back({i / 2, i});
    } else {
        for (int i = 2; i <= n; ++i) {
            int parent = rnd.next(1, i - 1);
            edges.push_back({parent, i});
        }
    }

    int average = rnd.next(1, 40);
    vector<long long> hay(n, average);

    if (mode != 4) {
        int moves = rnd.next(1, max(1, n * 2));
        for (int i = 0; i < moves; ++i) {
            int from = rnd.next(0, n - 1);
            int to = rnd.next(0, n - 1);
            if (from == to) continue;
            long long limit = min<long long>(20, hay[from] - 1);
            if (limit <= 0) continue;
            long long amount = rnd.next(1LL, limit);
            hay[from] -= amount;
            hay[to] += amount;
        }
    }

    if (mode == 5) {
        int rich = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i == rich || hay[i] <= 1) continue;
            long long amount = rnd.next(0LL, min<long long>(hay[i] - 1, 10));
            hay[i] -= amount;
            hay[rich] += amount;
        }
    }

    if (rnd.next(0, 1)) {
        vector<int> perm(n + 1);
        for (int i = 1; i <= n; ++i) perm[i] = i;
        shuffle(perm.begin() + 1, perm.end());

        vector<long long> relabeledHay(n);
        for (int oldLabel = 1; oldLabel <= n; ++oldLabel) {
            relabeledHay[perm[oldLabel] - 1] = hay[oldLabel - 1];
        }
        for (auto& edge : edges) {
            edge.first = perm[edge.first];
            edge.second = perm[edge.second];
            if (rnd.next(0, 1)) swap(edge.first, edge.second);
        }
        hay = relabeledHay;
    } else {
        for (auto& edge : edges) {
            if (rnd.next(0, 1)) swap(edge.first, edge.second);
        }
    }

    shuffle(edges.begin(), edges.end());

    println(n);
    println(hay);
    for (const auto& edge : edges) println(edge.first, edge.second);

    return 0;
}
