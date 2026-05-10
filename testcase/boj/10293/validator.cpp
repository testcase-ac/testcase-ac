#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// DSU with extra data to simulate groups and ranks to verify guarantees.
struct DSU {
    int n;
    vector<int> parent, sz, aliveGroup; // aliveGroup[root] == 1 if group exists
    DSU(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        parent.assign(n + 1, 0);
        sz.assign(n + 1, 1);
        aliveGroup.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    void merge(int X, int Y) {
        int rx = find(X);
        int ry = find(Y);
        ensuref(aliveGroup[ry] == 1, "Merging from a non-alive group Y=%d", Y);
        ensuref(aliveGroup[rx] == 1, "Merging into a non-alive group X=%d", X);
        if (rx == ry) {
            // merging a group into itself: allowed? Problem says merge group Y into X,
            // but doesn't explicitly forbid X==Y. We'll allow but no-op logically,
            // and do not kill the group.
            return;
        }
        // After merge, Y no longer exists as a group.
        aliveGroup[ry] = 0;
        // union by size
        if (sz[rx] < sz[ry]) swap(rx, ry);
        parent[ry] = rx;
        sz[rx] += sz[ry];
    }
    int groupSizeOfStudent(int j) {
        int r = find(j);
        return sz[r];
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 5, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 100000, "N");
        inf.readSpace();
        int L = inf.readInt(1, 200000, "L");
        inf.readEoln();

        // Initial configuration: N students, each in their own group 1..N.
        // Group IDs in operations refer to these numbers.
        DSU dsu(N);

        for (int i = 0; i < L; ++i) {
            int K = inf.readInt(1, 2, "K");
            if (K == 1) {
                inf.readSpace();
                int X = inf.readInt(1, N, "X");
                inf.readSpace();
                int Y = inf.readInt(1, N, "Y");
                inf.readEoln();

                // Validate semantics: group numbers X and Y must correspond to existing groups.
                // Our DSU tracks alive groups.
                ensuref(dsu.aliveGroup[X] == 1,
                        "Merge operation uses non-existing group X=%d at operation %d", X, i + 1);
                ensuref(dsu.aliveGroup[Y] == 1,
                        "Merge operation uses non-existing group Y=%d at operation %d", Y, i + 1);

                dsu.merge(X, Y);
            } else { // K == 2
                inf.readSpace();
                int J = inf.readInt(1, N, "J");
                inf.readEoln();

                // Rank of J in its group is size of its group minus number of students
                // with higher score in that group.
                // Since scores are 1..N increasing with student index, and rank 1 is highest score,
                // rank(J) = 1 + count of students in same group with index > J.
                // This is always between 1 and group size; we can at least ensure group size>=1.
                int gsz = dsu.groupSizeOfStudent(J);
                ensuref(gsz >= 1, "Internal error: group size < 1 for student %d", J);
            }
        }
    }

    inf.readEof();
}
