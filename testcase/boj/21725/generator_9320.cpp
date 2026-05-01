#include "testlib.h"
using namespace std;

struct DSU {
    vector<int> p, sz;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        p.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    int size(int x) {
        return sz[find(x)];
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
    }
};

struct Op {
    int type;        // 1 = merge, 2 = expense
    int x;
    long long v;     // for type 1: y, for type 2: c
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose n with bias towards small but with some variety up to 12
    int n;
    int t = rnd.next(0, 4);
    if (t == 0) n = 1;
    else if (t == 1) n = 2;
    else if (t == 2) n = 3;
    else if (t == 3) n = rnd.next(4, 8);
    else n = rnd.next(9, 12);

    DSU dsu(n);
    vector<Op> ops;

    if (n == 1) {
        // Single person: only expenses on single group
        int Emax = 30; // keep total lines small
        int E = rnd.next(0, Emax);
        for (int i = 0; i < E; i++) {
            int x = 1;
            int s = dsu.size(x); // =1
            long long maxShare = 100000000LL / s; // >=1

            int mode = rnd.next(0, 2);
            long long share;
            if (mode == 0) { // small
                long long up = min(1000LL, maxShare);
                share = rnd.next(1LL, up);
            } else if (mode == 1) { // medium
                long long low = min(1000LL, maxShare);
                long long up = min(1000000LL, maxShare);
                if (up < low) share = rnd.next(1LL, maxShare);
                else share = rnd.next(low, up);
            } else { // large, close to limit
                long long low = max(1LL, maxShare / 2);
                long long up = maxShare;
                if (up < low) up = low;
                share = rnd.next(low, up);
            }

            long long c = share * s; // s=1
            ops.push_back({2, x, c});
        }
    } else {
        // n >= 2: merges + expenses
        int Emax = 20; // so that m <= (n-1+20) <= 31
        int E = rnd.next(0, Emax);

        int mergeStyle = rnd.next(0, 2); // 0=random pairs, 1=star, 2=chain

        vector<int> perm(n);
        for (int i = 0; i < n; i++) perm[i] = i + 1;
        shuffle(perm.begin(), perm.end());

        int mergesDone = 0;
        int expensesDone = 0;

        while (mergesDone < n - 1 || expensesDone < E) {
            bool canMerge = (mergesDone < n - 1);
            bool canExpense = (expensesDone < E);
            int chooseType;

            if (!canMerge) chooseType = 2;
            else if (!canExpense) chooseType = 1;
            else {
                // Randomly choose merge or expense to interleave operations
                chooseType = (rnd.next(0, 1) == 0 ? 1 : 2);
            }

            if (chooseType == 1) {
                // Merge operation
                int x, y;
                if (mergeStyle == 0) {
                    // random valid pair from different components
                    do {
                        x = rnd.next(1, n);
                        y = rnd.next(1, n);
                    } while (x == y || dsu.find(x) == dsu.find(y));
                } else if (mergeStyle == 1) {
                    // star around a center perm[0]
                    x = perm[0];
                    y = perm[mergesDone + 1];
                } else {
                    // chain: (perm[i], perm[i+1])
                    x = perm[mergesDone];
                    y = perm[mergesDone + 1];
                }

                ops.push_back({1, x, (long long)y});
                dsu.unite(x, y);
                mergesDone++;
            } else {
                // Expense operation
                int x = rnd.next(1, n);
                int s = dsu.size(x);
                long long maxShare = 100000000LL / s; // >=1

                int mode = rnd.next(0, 2);
                long long share;
                if (mode == 0) { // small
                    long long up = min(1000LL, maxShare);
                    share = rnd.next(1LL, up);
                } else if (mode == 1) { // medium
                    long long low = min(1000LL, maxShare);
                    long long up = min(1000000LL, maxShare);
                    if (up < low) share = rnd.next(1LL, maxShare);
                    else share = rnd.next(low, up);
                } else { // large
                    long long low = max(1LL, maxShare / 2);
                    long long up = maxShare;
                    if (up < low) up = low;
                    share = rnd.next(low, up);
                }

                long long c = share * (long long)s; // divisible by group size
                ops.push_back({2, x, c});
                expensesDone++;
            }
        }
    }

    int m = (int)ops.size();
    println(n, m);
    for (const auto &op : ops) {
        if (op.type == 1) {
            println(1, op.x, (int)op.v);
        } else {
            println(2, op.x, op.v);
        }
    }

    return 0;
}
