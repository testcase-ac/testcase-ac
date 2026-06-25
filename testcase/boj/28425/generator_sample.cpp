#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? 1 : rnd.next(2, 14));
    int q = rnd.next(1, 18);

    vector<int> score(n + 1);
    int scoreMode = rnd.next(0, 3);
    for (int i = 1; i <= n; ++i) {
        if (scoreMode == 0) {
            score[i] = rnd.next(0, 20);
        } else if (scoreMode == 1) {
            score[i] = rnd.next(0, 1) ? rnd.next(0, 10000) : 0;
        } else if (scoreMode == 2) {
            score[i] = 10000;
        } else {
            score[i] = i * rnd.next(0, 7);
        }
    }

    vector<pair<int, int>> edges;
    if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(i - 1, i);
        }
    } else if (mode == 2) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            if (i != center) {
                edges.emplace_back(center, i);
            }
        }
    } else if (mode == 3) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(i / 2, i);
        }
    } else if (mode == 4) {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(rnd.next(max(1, i - 3), i - 1), i);
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.emplace_back(rnd.next(1, i - 1), i);
        }
    }

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    if (rnd.next(0, 1)) {
        shuffle(labels.begin(), labels.end());
    }
    for (auto& edge : edges) {
        edge.first = labels[edge.first - 1];
        edge.second = labels[edge.second - 1];
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
        cout << score[i];
    }
    cout << '\n';

    for (auto [u, v] : edges) {
        println(u, v);
    }

    vector<int> interesting;
    interesting.push_back(1);
    interesting.push_back(n);
    if (n >= 2) {
        interesting.push_back(labels[0]);
        interesting.push_back(labels[n - 1]);
    }

    for (int i = 0; i < q; ++i) {
        int r;
        int v;
        if (rnd.next(0, 99) < 45) {
            r = rnd.any(interesting);
        } else {
            r = rnd.next(1, n);
        }
        if (rnd.next(0, 99) < 35) {
            v = r;
        } else if (rnd.next(0, 99) < 60) {
            v = rnd.any(interesting);
        } else {
            v = rnd.next(1, n);
        }
        println(r, v);
    }

    return 0;
}
