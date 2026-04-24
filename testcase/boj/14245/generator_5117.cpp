#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

struct Op {
    int t, a, b, c;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters
    int n = rnd.next(1, 10);
    int init_max = rnd.next(0, 50);
    int m = rnd.next(1, 20);
    int upd_max = rnd.next(0, 100);
    double upd_prob = rnd.next(1, 9) * 0.1;  // between 0.1 and 0.9

    // Initial sequence
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rnd.next(0, init_max);
    }

    // Generate operations
    vector<Op> ops;
    int qcnt = 0;
    for (int i = 0; i < m; i++) {
        bool is_update = rnd.next() < upd_prob;
        if (is_update) {
            int l = rnd.next(0, n - 1);
            int r = rnd.next(l, n - 1);
            int c = rnd.next(0, upd_max);
            ops.push_back({1, l, r, c});
        } else {
            int idx = rnd.next(0, n - 1);
            ops.push_back({2, idx, 0, 0});
            qcnt++;
        }
    }
    // Ensure at least one query
    if (qcnt == 0) {
        int idx = rnd.next(0, m - 1);
        ops[idx].t = 2;
        qcnt++;
    }

    // Output
    println(n);
    println(a);
    println(m);
    for (auto &op : ops) {
        if (op.t == 1) {
            println(1, op.a, op.b, op.c);
        } else {
            println(2, op.a);
        }
    }
    return 0;
}
