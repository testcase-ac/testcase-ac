#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

static vector<int> relabel(const vector<int>& next) {
    int n = int(next.size()) - 1;
    vector<int> p(n + 1), inv(n + 1), out(n + 1);
    iota(p.begin() + 1, p.end(), 1);
    shuffle(p.begin() + 1, p.end());
    for (int i = 1; i <= n; ++i) inv[p[i]] = i;
    for (int i = 1; i <= n; ++i) out[p[i]] = p[next[i]];
    return out;
}

static void addCycle(vector<int>& f, const vector<int>& nodes) {
    int k = int(nodes.size());
    for (int i = 0; i < k; ++i) f[nodes[i]] = nodes[(i + 1) % k];
}

static vector<int> pureCycles(int n) {
    vector<int> f(n + 1), nodes(n);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());

    for (int pos = 0; pos < n;) {
        int remaining = n - pos;
        int len = remaining;
        if (remaining > 7) {
            len = rnd.next(2, min(remaining, 7));
            if (remaining - len == 1) ++len;
        }
        vector<int> cyc(nodes.begin() + pos, nodes.begin() + pos + len);
        addCycle(f, cyc);
        pos += len;
    }
    return relabel(f);
}

static vector<int> tailsIntoCycle(int n) {
    vector<int> f(n + 1);
    int cycleLen = rnd.next(2, min(n, 6));
    vector<int> cycle;
    for (int i = 1; i <= cycleLen; ++i) cycle.push_back(i);
    addCycle(f, cycle);

    for (int i = cycleLen + 1; i <= n; ++i) {
        int parent;
        if (rnd.next(3) == 0) parent = rnd.next(1, cycleLen);
        else parent = rnd.next(1, i - 1);
        f[i] = parent;
    }
    return relabel(f);
}

static vector<int> mutualPairsWithLeaves(int n) {
    vector<int> f(n + 1);
    int used = 0;
    while (used + 2 <= n && (used < 2 || rnd.next(2) == 0)) {
        f[used + 1] = used + 2;
        f[used + 2] = used + 1;
        used += 2;
    }
    if (used == n - 1) {
        f[used + 1] = rnd.next(1, used);
        used++;
    }
    for (int i = used + 1; i <= n; ++i) f[i] = rnd.next(1, i - 1);
    return relabel(f);
}

static vector<int> randomMapping(int n) {
    vector<int> f(n + 1);
    for (int i = 1; i <= n; ++i) {
        f[i] = rnd.next(1, n - 1);
        if (f[i] >= i) ++f[i];
    }
    return f;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 12);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0) n = 2;
        else if (tc == 1) n = rnd.next(3, 5);
        else n = rnd.next(4, 14);

        int mode = rnd.next(4);
        vector<int> f;
        if (mode == 0) f = pureCycles(n);
        else if (mode == 1) f = tailsIntoCycle(n);
        else if (mode == 2) f = mutualPairsWithLeaves(n);
        else f = randomMapping(n);

        println(n);
        vector<int> row(f.begin() + 1, f.end());
        println(row);
    }

    return 0;
}
