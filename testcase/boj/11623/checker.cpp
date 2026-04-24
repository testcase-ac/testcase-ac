#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    int n = inf.readInt(1, 100000, "n");
    int N = 2 * n;
    vector<int> out(N+1);
    // knights 1..n challenge f[i] in [n+1..2n]
    for (int i = 1; i <= n; i++) {
        int x = inf.readInt(n+1, N, format("f[%d]", i).c_str());
        out[i] = x;
    }
    // knights n+1..2n challenge s[i] in [1..n]
    for (int i = 1; i <= n; i++) {
        int x = inf.readInt(1, n, format("s[%d]", i).c_str());
        out[n + i] = x;
    }

    // Read contestant's kernel S: a list of integers until EOF
    vector<int> S;
    ouf.skipBlanks();
    while (!ouf.eof()) {
        int v = ouf.readInt(1, N, "kernel element");
        S.push_back(v);
        ouf.skipBlanks();
    }

    // Must output at least one knight
    if (S.empty())
        quitf(_wa, "kernel is empty");

    // Check uniqueness
    vector<char> inS(N+1, false);
    for (int v : S) {
        if (inS[v])
            quitf(_wa, "knight %d appears more than once in the kernel", v);
        inS[v] = true;
    }

    // Property 1: No knight in S is challenged by another knight in S.
    // That is, for every u in S, out[u] must not be in S.
    for (int u : S) {
        int t = out[u];
        if (inS[t]) {
            quitf(_wa,
                  "knight %d challenges knight %d, but both are in the kernel",
                  u, t);
        }
    }

    // Property 2: Every knight not in S is challenged by someone in S.
    vector<char> covered(N+1, false);
    for (int u : S) {
        covered[out[u]] = true;
    }
    for (int w = 1; w <= N; w++) {
        if (!inS[w] && !covered[w]) {
            quitf(_wa,
                  "knight %d is not in the kernel and is not challenged by any knight in the kernel",
                  w);
        }
    }

    // If all checks pass, accept
    quitf(_ok, "valid kernel of size %d", (int)S.size());
}
