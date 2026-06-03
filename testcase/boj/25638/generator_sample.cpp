#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 14);
    } else if (mode == 2) {
        n = rnd.next(3, 14);
    } else {
        n = rnd.next(4, 14);
    }

    vector<pair<int, int>> edges;
    if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i - 1, i});
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({1, i});
        }
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({i / 2, i});
        }
    } else if (mode == 4) {
        int spine = rnd.next(2, n - 1);
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

    vector<int> colors(n + 1);
    int colorMode = rnd.next(4);
    for (int i = 1; i <= n; ++i) {
        if (colorMode == 0) {
            colors[i] = i % 2;
        } else if (colorMode == 1) {
            colors[i] = (i == 1);
        } else if (colorMode == 2) {
            colors[i] = 0;
        } else {
            colors[i] = rnd.next(0, 1);
        }
    }

    vector<int> label(n + 1);
    iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 1, label.end());

    vector<int> permutedColors(n + 1);
    for (int oldVertex = 1; oldVertex <= n; ++oldVertex) {
        permutedColors[label[oldVertex]] = colors[oldVertex];
    }
    for (auto& edge : edges) {
        edge = {label[edge.first], label[edge.second]};
        if (rnd.next(2)) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.begin(), edges.end());

    int q = rnd.next(1, n);
    vector<int> queries;
    for (int i = 0; i < q; ++i) {
        if (i < min(q, n) && rnd.next(3) == 0) {
            queries.push_back(i + 1);
        } else {
            queries.push_back(rnd.next(1, n));
        }
    }
    shuffle(queries.begin(), queries.end());

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << permutedColors[i];
    }
    cout << '\n';
    for (const auto& edge : edges) {
        println(edge.first, edge.second);
    }
    println(q);
    for (int query : queries) {
        println(query);
    }

    return 0;
}
