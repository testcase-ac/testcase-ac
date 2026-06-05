#include "testlib.h"

#include <algorithm>
#include <array>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.emplace_back(i - 1, i);
    }
    return edges;
}

vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(1, n);
    for (int i = 1; i <= n; ++i) {
        if (i != center) {
            edges.emplace_back(center, i);
        }
    }
    return edges;
}

vector<pair<int, int>> makeBinaryTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.emplace_back(i / 2, i);
    }
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(2, n);
    for (int i = 2; i <= handle; ++i) {
        edges.emplace_back(i - 1, i);
    }
    for (int i = handle + 1; i <= n; ++i) {
        edges.emplace_back(handle, i);
    }
    return edges;
}

vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        edges.emplace_back(rnd.next(1, i - 1), i);
    }
    return edges;
}

int clampedBeauty(int value) {
    return max(1, min(1000, value));
}

array<int, 3> makeBeauty(int index, int mode) {
    if (mode == 0) {
        int base = rnd.next(1, 1000);
        return {base, base, base};
    }
    if (mode == 1) {
        int preferred = (index + rnd.next(0, 2)) % 3;
        array<int, 3> value = {rnd.next(1, 30), rnd.next(1, 30), rnd.next(1, 30)};
        value[preferred] = rnd.next(850, 1000);
        return value;
    }
    if (mode == 2) {
        int base = rnd.next(1, 900);
        int spread = rnd.next(0, 100);
        return {clampedBeauty(base), clampedBeauty(base + rnd.next(0, spread)),
                clampedBeauty(base + rnd.next(0, spread))};
    }
    if (mode == 3) {
        int high = rnd.next(700, 1000);
        int low = rnd.next(1, 80);
        int mid = rnd.next(81, 699);
        array<int, 3> value = {low, mid, high};
        shuffle(value.begin(), value.end());
        return value;
    }
    return {rnd.next(1, 1000), rnd.next(1, 1000), rnd.next(1, 1000)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 6);
    } else if (sizeMode == 2) {
        n = rnd.next(7, 15);
    } else if (sizeMode == 3) {
        n = rnd.next(16, 30);
    } else {
        n = rnd.next(31, 60);
    }

    vector<pair<int, int>> edges;
    int treeMode = rnd.next(0, 4);
    if (n == 1) {
        edges.clear();
    } else if (treeMode == 0) {
        edges = makePath(n);
    } else if (treeMode == 1) {
        edges = makeStar(n);
    } else if (treeMode == 2) {
        edges = makeBinaryTree(n);
    } else if (treeMode == 3) {
        edges = makeBroom(n);
    } else {
        edges = makeRandomTree(n);
    }

    vector<int> perm(n + 1);
    for (int i = 1; i <= n; ++i) {
        perm[i] = i;
    }
    shuffle(perm.begin() + 1, perm.end());
    for (auto& edge : edges) {
        edge.first = perm[edge.first];
        edge.second = perm[edge.second];
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    int beautyMode = rnd.next(0, 4);
    println(n);
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }
    for (int i = 1; i <= n; ++i) {
        array<int, 3> beauty = makeBeauty(i, beautyMode);
        println(beauty[0], beauty[1], beauty[2]);
    }

    return 0;
}
