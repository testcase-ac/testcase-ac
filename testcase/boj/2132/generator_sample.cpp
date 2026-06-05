#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        edges.push_back({i, i + 1});
    }
    return edges;
}

vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(1, n);
    for (int i = 1; i <= n; ++i) {
        if (i != center) {
            edges.push_back({center, i});
        }
    }
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(2, n);
    for (int i = 1; i < handle; ++i) {
        edges.push_back({i, i + 1});
    }
    for (int i = handle + 1; i <= n; ++i) {
        edges.push_back({handle, i});
    }
    return edges;
}

vector<pair<int, int>> makeBinaryLike(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i / 2, i});
    }
    return edges;
}

vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i, rnd.next(1, i - 1)});
    }
    return edges;
}

vector<long long> makeFruit(int n) {
    vector<long long> fruit(n + 1);
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            fruit[i] = rnd.next(0, 9);
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            fruit[i] = rnd.next(0, 1) ? 0 : rnd.next(1, 20);
        }
    } else if (mode == 2) {
        long long value = rnd.next(0, 5);
        fill(fruit.begin() + 1, fruit.end(), value);
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            fruit[i] = rnd.next(0, 3);
        }
        fruit[rnd.next(1, n)] = rnd.next(100, 100000);
        fruit[rnd.next(1, n)] = rnd.next(100, 100000);
    } else {
        long long remaining = 2147483647LL;
        for (int i = 1; i <= n; ++i) {
            long long cap = min<long long>(remaining, 2000000000LL / n + 1000);
            fruit[i] = rnd.next(0LL, cap);
            remaining -= fruit[i];
        }
    }

    return fruit;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0) ? 1 : rnd.next(2, 14);

    vector<pair<int, int>> edges;
    if (mode == 0) {
        edges = {};
    } else if (mode == 1) {
        edges = makePath(n);
    } else if (mode == 2) {
        edges = makeStar(n);
    } else if (mode == 3) {
        edges = makeBroom(n);
    } else if (mode == 4) {
        edges = makeBinaryLike(n);
    } else {
        edges = makeRandomTree(n);
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());
    for (auto& edge : edges) {
        edge.first = label[edge.first];
        edge.second = label[edge.second];
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    vector<long long> fruit = makeFruit(n);
    shuffle(fruit.begin() + 1, fruit.end());

    println(n);
    println(vector<long long>(fruit.begin() + 1, fruit.end()));
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
