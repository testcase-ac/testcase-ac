#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

vector<pair<int, int>> makeTree(int n, int mode) {
    vector<pair<int, int>> edges;
    if (n <= 1) {
        return edges;
    }

    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(i - 1, i);
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) {
                edges.emplace_back(center, i);
            }
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(i / 2, i);
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(rnd.next(1, i - 1), i);
        }
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(2) == 0) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(100);
    int n;
    if (sizeMode < 10) {
        n = 1;
    } else if (sizeMode < 75) {
        n = rnd.next(2, 10);
    } else {
        n = rnd.next(11, 25);
    }

    int q = rnd.next(1, min(60, max(1, 3 * n + 10)));
    int treeMode = rnd.next(4);
    int queryMode = rnd.next(4);

    vector<pair<int, int>> edges = makeTree(n, treeMode);
    vector<vector<int>> queries;
    queries.reserve(q);

    bool hasTypeTwo = false;
    for (int i = 0; i < q; ++i) {
        bool typeTwo = n == 1 || rnd.next(100) < (queryMode == 0 ? 20 : queryMode == 1 ? 50 : queryMode == 2 ? 80 : 35);
        if (i == q - 1 && !hasTypeTwo) {
            typeTwo = true;
        }

        if (typeTwo) {
            int x = rnd.next(1, n);
            queries.push_back({2, x});
            hasTypeTwo = true;
        } else {
            int u = rnd.next(1, n);
            int v = rnd.next(1, n - 1);
            if (v >= u) {
                ++v;
            }
            queries.push_back({1, u, v});
        }
    }

    println(n);
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }
    println(q);
    for (const auto& query : queries) {
        println(query);
    }

    return 0;
}
