#include "testlib.h"

#include <algorithm>
#include <set>
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

vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        int parent = rnd.next(1, i - 1);
        edges.emplace_back(parent, i);
    }
    return edges;
}

vector<int> makeValues(int n) {
    int mode = rnd.next(0, 4);
    vector<int> values;

    if (mode == 0) {
        int start = rnd.next(-30, 30);
        int step = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            values.push_back(start + i * step);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            values.push_back(i % 2 == 0 ? i / 2 + 1 : -(i / 2 + 1));
        }
    } else if (mode == 2) {
        int start = 1000000000 - n + 1;
        for (int i = 0; i < n; ++i) {
            values.push_back(start + i);
        }
    } else if (mode == 3) {
        int start = -1000000000;
        for (int i = 0; i < n; ++i) {
            values.push_back(start + i);
        }
    } else {
        set<int> seen;
        while ((int)values.size() < n) {
            int value = rnd.next(-100, 100);
            if (seen.insert(value).second) {
                values.push_back(value);
            }
        }
    }

    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 3);
    int n;
    if (sizeMode == 0) {
        n = 2;
    } else if (sizeMode == 1) {
        n = rnd.next(3, 8);
    } else {
        n = rnd.next(9, 25);
    }

    vector<int> values = makeValues(n);

    int treeMode = rnd.next(0, 3);
    vector<pair<int, int>> edges;
    if (treeMode == 0) {
        edges = makePath(n);
    } else if (treeMode == 1) {
        edges = makeStar(n);
    } else if (treeMode == 2) {
        edges = makeBinaryTree(n);
    } else {
        edges = makeRandomTree(n);
    }

    vector<int> labels(n);
    for (int i = 0; i < n; ++i) {
        labels[i] = i + 1;
    }
    shuffle(labels.begin(), labels.end());
    shuffle(edges.begin(), edges.end());

    println(n);
    println(values);
    for (auto [a, b] : edges) {
        if (rnd.next(0, 1) == 1) {
            swap(a, b);
        }
        println(labels[a - 1], labels[b - 1]);
    }

    return 0;
}
