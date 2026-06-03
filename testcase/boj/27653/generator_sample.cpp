#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = (mode <= 1) ? rnd.next(2, 8) : rnd.next(2, 24);

    vector<long long> a(n + 1);
    int weightMode = rnd.next(0, 6);
    if (weightMode == 0) {
        long long value = rnd.next(0, 20);
        fill(a.begin() + 1, a.end(), value);
    } else if (weightMode == 1) {
        for (int i = 1; i <= n; ++i) {
            a[i] = rnd.next(0, 1) ? 1000000000LL : 0LL;
        }
    } else if (weightMode == 2) {
        for (int i = 1; i <= n; ++i) {
            a[i] = rnd.next(0, 12);
        }
    } else if (weightMode == 3) {
        long long start = rnd.next(0, 10);
        long long step = rnd.next(0, 4);
        for (int i = 1; i <= n; ++i) {
            a[i] = start + step * (i - 1);
        }
    } else if (weightMode == 4) {
        long long high = rnd.next(10, 100);
        long long low = rnd.next(0, 9);
        for (int i = 1; i <= n; ++i) {
            a[i] = (i % 2 == 0) ? low : high;
        }
    } else if (weightMode == 5) {
        long long base = rnd.next(0, 1000);
        for (int i = 1; i <= n; ++i) {
            a[i] = min(1000000000LL, base + rnd.next(0, 5));
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            a[i] = rnd.next(0, 1000000000);
        }
    }

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
        for (int i = 2; i <= n; ++i) {
            edges.push_back({rnd.next(max(1, i - 4), i - 1), i});
        }
    } else {
        for (int i = 2; i <= n; ++i) {
            edges.push_back({rnd.next(1, i - 1), i});
        }
    }

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = i;
    }
    if (rnd.next(0, 1)) {
        shuffle(label.begin() + 1, label.end());
    }
    shuffle(edges.begin(), edges.end());
    for (auto& edge : edges) {
        if (rnd.next(0, 1)) {
            swap(edge.first, edge.second);
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            putchar(' ');
        }
        printf("%lld", a[label[i]]);
    }
    putchar('\n');
    for (auto [u, v] : edges) {
        println(label[u], label[v]);
    }

    return 0;
}
