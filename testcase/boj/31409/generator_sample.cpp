#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

static vector<int> shuffledLabels(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end());
    return p;
}

static void relabel(vector<int>& a) {
    int n = int(a.size()) - 1;
    vector<int> p = shuffledLabels(n);
    vector<int> b(n + 1);
    for (int i = 1; i <= n; ++i) {
        b[p[i - 1]] = p[a[i] - 1];
    }
    a.swap(b);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(19, 80);
    }

    vector<int> a(n + 1);

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            a[i] = i;
        }
    } else if (mode == 1) {
        vector<int> nodes = shuffledLabels(n);
        int pos = 0;
        while (pos < n) {
            int remaining = n - pos;
            int len = remaining == 1 ? 1 : rnd.next(2, min(remaining, 7));
            if (remaining - len == 1) {
                ++len;
            }
            for (int j = 0; j < len; ++j) {
                int u = nodes[pos + j];
                int v = nodes[pos + (j + 1) % len];
                a[u] = v;
            }
            pos += len;
        }
    } else if (mode == 2) {
        int cycleLen = rnd.next(2, min(n, 6));
        for (int i = 1; i < cycleLen; ++i) {
            a[i] = i + 1;
        }
        a[cycleLen] = 1;
        for (int i = cycleLen + 1; i <= n; ++i) {
            a[i] = rnd.next(1, i - 1);
        }
        relabel(a);
    } else if (mode == 3) {
        int hub = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            a[i] = hub;
        }
    } else if (mode == 4) {
        for (int i = 1; i <= n; ++i) {
            if (rnd.next(0, 99) < 35) {
                a[i] = i;
            } else {
                a[i] = rnd.next(1, n);
            }
        }
    } else {
        vector<int> nodes = shuffledLabels(n);
        int anchor = nodes[0];
        int partner = nodes[1];
        a[anchor] = partner;
        a[partner] = anchor;
        for (int i = 2; i < n; ++i) {
            int u = nodes[i];
            if (rnd.next(0, 99) < 25) {
                a[u] = u;
            } else {
                a[u] = nodes[rnd.next(0, i - 1)];
            }
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';

    return 0;
}
