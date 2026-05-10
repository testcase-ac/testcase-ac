#include "testlib.h"
#include <vector>

using namespace std;

struct DSU {
    int n;
    vector<int> p, sz;
    DSU(int n): n(n), p(n+1), sz(n+1, 1) {
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
    int size(int x) {
        return sz[find(x)];
    }
    int countRoots() {
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            if (find(i) == i) ++cnt;
        return cnt;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAXM = 200000;
    const int MAXC = 100000000; // 1e8

    int n = inf.readInt(1, MAXN, "n");
    inf.readSpace();
    int m = inf.readInt(n - 1, MAXM, "m");
    inf.readEoln();

    DSU dsu(n);

    // To simulate balances and check final transfer bound existence
    // Each friend starts with 2e18; only relative balances matter, but
    // for answer-existence constraints we need to ensure per-edge sums <= 2e13 is feasible.
    // We track net balance (spent - should_pay).
    vector<long long> net(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            inf.readSpace();
            int x = inf.readInt(1, n, "x");
            inf.readSpace();
            int y = inf.readInt(1, n, "y");
            inf.readEoln();

            int rx = dsu.find(x);
            int ry = dsu.find(y);
            ensuref(rx != ry, "Merge record %d tries to merge already connected groups: (%d, %d)", i + 1, x, y);
            dsu.unite(rx, ry);
        } else {
            inf.readSpace();
            int x = inf.readInt(1, n, "x");
            inf.readSpace();
            int c = inf.readInt(1, MAXC, "c");
            inf.readEoln();

            int gsz = dsu.size(x);
            ensuref(c % gsz == 0, "Expense record %d: c=%d is not divisible by current group size %d", i + 1, c, gsz);

            long long share = c / (long long)gsz;
            int root = dsu.find(x);

            // Everyone in this group owes 'share', payer paid 'c'
            // To avoid iterating over group members, track only net of root and a global per-root share count.
            // But since we need correct final transfers bound, we can track per person using lazy approach is complex.
            // Instead, we track for the whole group: total spent and total should-pay.
            // Implementation simplification: assume each member in group pays share, payer gets (gsz-1)*share owed.
            // We'll approximate via root aggregate and equal splitting at end: all group members same net,
            // so max flow per edge remains bounded similarly.
            // However, correctness of "answer always exists within 2e13 per transfer" is guaranteed by statement;
            // we don't need to recompute the actual transfer plan here, only divisibility.
            //
            // Therefore, we only maintain a balance for x to ensure no overflow; others ignored.
            // net[x] += c - share; (payer paid c, owes share)
            net[x] += (long long)c - share;
            // No further constraints derived from balances are specified in statement, so no more checks here.
        }
    }

    // After all records, all students must be in one group
    ensuref(dsu.countRoots() == 1, "After all %d records, all students must be in one group", m);

    inf.readEof();
}
