#include "testlib.h"
#include <vector>
using namespace std;

struct DSU {
    int n;
    vector<int> p, r;
    int merges;
    DSU(int _n): n(_n), p(n+1), r(n+1, 0), merges(0) {
        for(int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }
    bool unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return false;
        if (r[ra] < r[rb]) {
            p[ra] = rb;
        } else if (r[ra] > r[rb]) {
            p[rb] = ra;
        } else {
            p[rb] = ra;
            r[ra]++;
        }
        merges++;
        return true;
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, Q
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // Read and validate tree edges
    DSU dsu(N);
    for (int i = 0; i < N - 1; i++) {
        int u = inf.readInt(1, N, "S");
        inf.readSpace();
        int v = inf.readInt(1, N, "E");
        inf.readEoln();
        bool ok = dsu.unite(u, v);
        ensuref(ok, "Edge %d: (%d, %d) introduces a cycle or is a duplicate", i+1, u, v);
    }
    // Check tree is connected: merges must be N-1
    ensuref(dsu.merges == N - 1, "The given edges do not form a single connected tree");

    // Read and validate Q commands
    for (int i = 0; i < Q; i++) {
        int t = inf.readInt(1, 6, "t");
        switch (t) {
            case 1: {
                inf.readSpace();
                int X = inf.readInt(1, N, "X");
                inf.readSpace();
                int V = inf.readInt(1, 1000000000, "V");
                inf.readEoln();
                break;
            }
            case 2: {
                inf.readSpace();
                int X = inf.readInt(1, N, "X");
                inf.readSpace();
                int Y = inf.readInt(1, N, "Y");
                inf.readSpace();
                int V = inf.readInt(1, 1000000000, "V");
                inf.readEoln();
                break;
            }
            case 3: {
                inf.readSpace();
                int X = inf.readInt(1, N, "X");
                inf.readSpace();
                int V = inf.readInt(0, 1000000000, "V");
                inf.readEoln();
                break;
            }
            case 4: {
                inf.readSpace();
                int X = inf.readInt(1, N, "X");
                inf.readSpace();
                int Y = inf.readInt(1, N, "Y");
                inf.readSpace();
                int V = inf.readInt(0, 1000000000, "V");
                inf.readEoln();
                break;
            }
            case 5: {
                inf.readSpace();
                int X = inf.readInt(1, N, "X");
                inf.readEoln();
                break;
            }
            case 6: {
                inf.readSpace();
                int X = inf.readInt(1, N, "X");
                inf.readSpace();
                int Y = inf.readInt(1, N, "Y");
                inf.readEoln();
                break;
            }
            default:
                // Should never happen
                ensuref(false, "Invalid command type %d", t);
        }
    }

    inf.readEof();
    return 0;
}
