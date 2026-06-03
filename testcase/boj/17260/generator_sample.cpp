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
    int center = rnd.next(1, n);
    vector<pair<int, int>> edges;
    for (int i = 1; i <= n; ++i) {
        if (i != center) {
            edges.push_back({center, i});
        }
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

vector<pair<int, int>> relabelEdges(int n, vector<pair<int, int>> edges) {
    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
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

vector<int> makeHeights(int n, int mode) {
    vector<int> heights(n + 1);
    int base = rnd.next(1, 40);

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            heights[i] = base + rnd.next(0, 8);
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            heights[i] = base + 2 * i + rnd.next(0, 1);
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            heights[i] = base + 2 * (n - i) + rnd.next(0, 1);
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            heights[i] = base + rnd.any(vector<int>{0, 1, 2, 4, 8, 16});
        }
    }

    return heights;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 14);
    int k = rnd.next(1, n);
    int shape = rnd.next(4);
    int heightMode = rnd.next(4);

    vector<pair<int, int>> edges;
    if (shape == 0) {
        edges = makePath(n);
    } else if (shape == 1) {
        edges = makeStar(n);
    } else if (shape == 2) {
        edges = makeRandomTree(n);
    } else {
        int spine = rnd.next(1, n);
        edges = makePath(spine);
        for (int i = spine + 1; i <= n; ++i) {
            edges.push_back({rnd.next(1, spine), i});
        }
    }

    vector<int> heights = makeHeights(n, heightMode);
    edges = relabelEdges(n, edges);

    println(n, k);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << heights[i];
    }
    cout << '\n';
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }

    return 0;
}
