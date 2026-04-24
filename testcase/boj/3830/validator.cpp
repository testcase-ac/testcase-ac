#include "testlib.h"
#include <vector>
#include <string>
#include <cassert>
#include <cmath>
using namespace std;

static const int MAXN = 100000;

int N, M;
// DSU with potential (weight difference)
int parent_[MAXN+5];
long long delta_[MAXN+5]; // delta_[x] = weight[x] - weight[parent_[x]]

int findRoot(int x) {
    if (parent_[x] == x) return x;
    int p = parent_[x];
    int r = findRoot(p);
    // accumulate delta
    delta_[x] += delta_[p];
    parent_[x] = r;
    return r;
}
// ensure path compressed, then return delta_[x]: weight[x] - weight[root]
long long getDist(int x) {
    int r = findRoot(x);
    (void)r;
    return delta_[x];
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    while (true) {
        // Read N, M (with termination 0 0)
        int n = inf.readInt(0, MAXN, "N");
        inf.readSpace();
        int m = inf.readInt(0, MAXN, "M");
        inf.readEoln();
        if (n == 0 && m == 0) {
            break;
        }
        // Validate N, M
        ensuref(n >= 2, "N must be at least 2, got %d", n);
        ensuref(m >= 1, "M must be at least 1, got %d", m);

        // Initialize DSU for this test
        N = n; M = m;
        for (int i = 1; i <= N; i++) {
            parent_[i] = i;
            delta_[i] = 0;
        }

        // Process M operations
        for (int i = 1; i <= M; i++) {
            // Read operation type
            string op = inf.readToken("[!?]", "op");
            inf.readSpace();
            if (op == "!") {
                int a = inf.readInt(1, N, "a");
                inf.readSpace();
                int b = inf.readInt(1, N, "b");
                inf.readSpace();
                int w = inf.readInt(0, 1000000, "w");
                inf.readEoln();

                ensuref(a != b,
                        "Measurement #%d has same samples a=b=%d", i, a);

                // weight[b] - weight[a] = w
                int ra = findRoot(a);
                int rb = findRoot(b);
                long long da = getDist(a); // weight[a] - weight[ra]
                long long db = getDist(b); // weight[b] - weight[rb]

                if (ra == rb) {
                    // Already connected: check consistency
                    long long cur = db - da;
                    ensuref(cur == w,
                            "Inconsistent measurement #%d: ! %d %d %d, but existing difference is %lld",
                            i, a, b, w, cur);
                } else {
                    // Merge ra under rb, set delta_[ra] s.t.
                    // delta_[ra] = weight[ra] - weight[rb]
                    // We have weight[a] = weight[ra] + da
                    //        weight[b] = weight[rb] + db
                    // We need weight[b] - weight[a] = w
                    // => (weight[rb] + db) - (weight[ra] + da) = w
                    // => weight[ra] - weight[rb] = db - da - w
                    parent_[ra] = rb;
                    delta_[ra] = (db - da - (long long)w);
                }
            } else { // op == "?"
                int a = inf.readInt(1, N, "a");
                inf.readSpace();
                int b = inf.readInt(1, N, "b");
                inf.readEoln();

                // If connected, the answer is computable: check abs diff <= 1e6
                int ra = findRoot(a);
                int rb = findRoot(b);
                if (ra == rb) {
                    long long da = getDist(a);
                    long long db = getDist(b);
                    long long diff = db - da;
                    ensuref(diff >= -1000000LL && diff <= 1000000LL,
                            "Query #%d asks ? %d %d with |difference|=%lld > 1e6",
                            i, a, b, diff);
                }
                // else unknown: no further validation
            }
        }
    }

    inf.readEof();
    return 0;
}
