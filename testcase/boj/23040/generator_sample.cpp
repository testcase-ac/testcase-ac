#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makeTree(int n, int mode) {
    vector<pair<int, int>> edges;
    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i - 1, i});
        }
    } else if (mode == 1) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) {
                edges.push_back({center, i});
            }
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i / 2, i});
        }
    } else if (mode == 3) {
        int spine = rnd.next(2, n);
        for (int i = 2; i <= spine; ++i) {
            edges.push_back({i - 1, i});
        }
        for (int i = spine + 1; i <= n; ++i) {
            edges.push_back({rnd.next(1, spine), i});
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({rnd.next(1, i - 1), i});
        }
    }

    shuffle(edges.begin(), edges.end());
    return edges;
}

string makeColors(int n, int mode) {
    string colors(n, 'R');
    if (mode == 0) {
        return colors;
    }
    if (mode == 1) {
        return string(n, 'B');
    }
    if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            colors[i] = (i % 2 == 0 ? 'B' : 'R');
        }
    } else if (mode == 3) {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i < split; ++i) {
            colors[i] = 'B';
        }
    } else if (mode == 4) {
        int blackCount = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < blackCount; ++i) {
            colors[rnd.next(0, n - 1)] = 'B';
        }
    } else {
        int redProbability = rnd.next(25, 85);
        for (int i = 0; i < n; ++i) {
            colors[i] = (rnd.next(1, 100) <= redProbability ? 'R' : 'B');
        }
    }
    return colors;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    if (sizeMode == 0) {
        n = 2;
    } else if (sizeMode <= 2) {
        n = rnd.next(3, 8);
    } else {
        n = rnd.next(9, 30);
    }

    vector<pair<int, int>> edges = makeTree(n, rnd.next(0, 4));
    string colors = makeColors(n, rnd.next(0, 5));

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    shuffle(label.begin() + 1, label.end());

    string relabeledColors(n, 'R');
    for (int i = 1; i <= n; ++i) {
        relabeledColors[label[i] - 1] = colors[i - 1];
    }

    println(n);
    for (auto [u, v] : edges) {
        println(label[u], label[v]);
    }
    println(relabeledColors);

    return 0;
}
