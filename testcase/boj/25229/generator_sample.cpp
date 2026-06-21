#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i - 1, i});
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

vector<pair<int, int>> makeBinaryTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({i / 2, i});
    }
    return edges;
}

vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.push_back({rnd.next(1, i - 1), i});
    }
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(2, n);
    for (int i = 2; i <= handle; ++i) {
        edges.push_back({i - 1, i});
    }
    for (int i = handle + 1; i <= n; ++i) {
        edges.push_back({handle, i});
    }
    return edges;
}

vector<int> makeValues(int n) {
    const vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
                                41, 43, 47, 53, 59, 61, 67, 71, 73, 79,
                                83, 89, 97};
    const vector<int> composites = {4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20,
                                    21, 22, 24, 25, 27, 28, 30, 36, 42, 49,
                                    60, 72, 84, 90, 96, 100};

    vector<int> values(n);
    int mode = rnd.next(0, 5);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            values[i] = rnd.next(1, 100);
        } else if (mode == 1) {
            values[i] = rnd.any(primes);
        } else if (mode == 2) {
            values[i] = rnd.any(composites);
        } else if (mode == 3) {
            values[i] = (i % 2 == 0 ? rnd.any(primes) : rnd.any(composites));
        } else if (mode == 4) {
            int base = rnd.any(vector<int>{2, 3, 5, 7});
            values[i] = base * rnd.next(1, 100 / base);
        } else {
            values[i] = rnd.any(vector<int>{1, 1, 1, 2, 3, 4, 6, 30, 97, 100});
        }
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 9);
    int n = 2;
    if (sizeMode == 0) {
        n = 2;
    } else if (sizeMode <= 3) {
        n = rnd.next(3, 8);
    } else if (sizeMode <= 7) {
        n = rnd.next(9, 20);
    } else {
        n = rnd.next(21, 35);
    }

    vector<pair<int, int>> edges;
    int treeMode = rnd.next(0, 4);
    if (treeMode == 0) {
        edges = makePath(n);
    } else if (treeMode == 1) {
        edges = makeStar(n);
    } else if (treeMode == 2) {
        edges = makeBinaryTree(n);
    } else if (treeMode == 3) {
        edges = makeRandomTree(n);
    } else {
        edges = makeBroom(n);
    }

    vector<int> perm(n + 1);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin() + 1, perm.end());
    for (auto& edge : edges) {
        edge.first = perm[edge.first];
        edge.second = perm[edge.second];
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    println(n);
    for (int value : makeValues(n)) {
        println(value);
    }
    for (auto [a, b] : edges) {
        println(a, b);
    }

    return 0;
}
