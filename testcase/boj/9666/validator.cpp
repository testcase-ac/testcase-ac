#include "testlib.h"
#include <vector>
using namespace std;

static vector<int> parent_, parity_, rnk_;

int find_set(int v) {
    if (parent_[v] == v)
        return v;
    int p = parent_[v];
    int root = find_set(p);
    // compress path and update parity to root
    parity_[v] ^= parity_[p];
    return parent_[v] = root;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();
    // Read M
    int M = inf.readInt(1, 300000, "M");
    inf.readEoln();

    // Initialize DSU with parity
    parent_.assign(N, 0);
    parity_.assign(N, 0);
    rnk_.assign(N, 0);
    for (int i = 0; i < N; i++) {
        parent_[i] = i;
        parity_[i] = 0;
        rnk_[i] = 0;
    }

    bool odd_cycle_found = false;
    for (int i = 0; i < M; i++) {
        // Read a fight
        int u_orig = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v_orig = inf.readInt(1, N, "v_i");
        inf.readEoln();

        // No loops allowed
        ensuref(u_orig != v_orig,
                "Loop detected at fight index %d: both fighters are %d", i+1, u_orig);

        int u = u_orig - 1;
        int v = v_orig - 1;

        if (!odd_cycle_found) {
            // find roots and parities
            int ru = find_set(u);
            int rv = find_set(v);
            int pu = parity_[u];
            int pv = parity_[v];
            if (ru == rv) {
                // if u and v have same parity, this edge makes odd cycle
                if (pu == pv) {
                    odd_cycle_found = true;
                }
            } else {
                // union by rank, and set parity
                // we want parity_[child] so that pu ^ parity_child = pv ^ 1
                int need = pu ^ pv ^ 1;
                if (rnk_[ru] < rnk_[rv]) {
                    parent_[ru] = rv;
                    parity_[ru] = need;
                } else {
                    parent_[rv] = ru;
                    parity_[rv] = need;
                    if (rnk_[ru] == rnk_[rv])
                        rnk_[ru]++;
                }
            }
        }
    }

    // The problem guarantees that at some fight same-team must occur
    ensuref(odd_cycle_found,
            "Invalid input: the full fighting schedule is bipartite (no same-team fight ever occurs)");

    inf.readEof();
    return 0;
}
