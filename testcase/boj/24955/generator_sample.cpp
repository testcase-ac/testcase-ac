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
        int parent = rnd.next(1, i - 1);
        edges.push_back({parent, i});
    }
    return edges;
}

int smallPower10(int digits) {
    int value = 1;
    for (int i = 1; i < digits; ++i) {
        value *= 10;
    }
    return value;
}

int randomValue() {
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        return rnd.next(1, 9);
    }
    if (mode == 1) {
        int digits = rnd.next(2, 9);
        int lo = smallPower10(digits);
        int hi = min(1000000000, lo * 10 - 1);
        return rnd.next(lo, hi);
    }
    if (mode == 2) {
        return rnd.any(vector<int>{10, 99, 100, 1000, 1000000000});
    }
    return rnd.next(1, 1000000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int shape = rnd.next(0, 4);
    int n = rnd.next(2, shape == 0 ? 30 : 20);
    int q = rnd.next(1, min(60, n * 3));

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = randomValue();
    }

    vector<pair<int, int>> edges;
    if (shape == 0) {
        edges = makePath(n);
    } else if (shape == 1) {
        edges = makeStar(n);
    } else if (shape == 2) {
        edges = makeBinaryLike(n);
    } else {
        edges = makeRandomTree(n);
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

    println(n, q);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << label[i];
    }
    cout << '\n';
    for (auto edge : edges) {
        println(edge.first, edge.second);
    }

    for (int i = 0; i < q; ++i) {
        int mode = rnd.next(0, 4);
        int x = rnd.next(1, n);
        int y = rnd.next(1, n);
        if (mode == 0) {
            y = x;
        } else if (mode == 1) {
            auto edge = rnd.any(edges);
            x = edge.first;
            y = edge.second;
        } else if (mode == 2 && shape == 0) {
            x = perm[1];
            y = perm[n];
            if (rnd.next(0, 1)) {
                swap(x, y);
            }
        }
        println(x, y);
    }

    return 0;
}
