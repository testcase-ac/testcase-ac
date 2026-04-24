#include "testlib.h"
#include <vector>
#include <cmath>
#include <string>
using namespace std;

int N;
int sz;
vector<int> a;
vector<bool> used;

// DFS to compute subtree sums and check the difference condition.
// i: current node index in array (0-based).
// level: level of this node (root is level 0).
long long dfs(int i, int level) {
    // if this node has no children, it's a leaf
    int lc = 2*i + 1;
    if (lc >= sz) {
        // leaf: sum is just its own value
        return a[i];
    }
    int rc = lc + 1;
    // compute sums of left and right subtrees
    long long sumL = dfs(lc, level + 1);
    long long sumR = dfs(rc, level + 1);
    long long diff = llabs(sumL - sumR);
    long long expected = 1LL << level;
    if (diff != expected) {
        // report wrong difference
        ouf.quitf(_wa,
            "at node index %d (level %d): left sum = %lld, right sum = %lld, "
            "abs difference = %lld, expected = %lld",
            i + 1, level, sumL, sumR, diff, expected);
    }
    // include this node's own value in the sum returned
    return sumL + sumR + a[i];
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    N = inf.readInt();
    if (N < 1 || N > 15) {
        // invalid test input
        inf.quitf(_fail, "invalid N = %d", N);
    }
    // total nodes in a perfect binary tree of level N
    sz = (1 << N) - 1;
    a.resize(sz);
    used.assign(sz + 1, false);

    // Read contestant's output: exactly sz integers in [1..sz]
    for (int i = 0; i < sz; i++) {
        a[i] = ouf.readInt(1, sz, format("value[%d]", i+1).c_str());
        if (used[a[i]]) {
            ouf.quitf(_wa, "value %d is used more than once", a[i]);
        }
        used[a[i]] = true;
    }
    // there should be no extra tokens
    ouf.readEof();

    // Check that all values from 1 to sz appear
    for (int v = 1; v <= sz; v++) {
        if (!used[v]) {
            ouf.quitf(_wa, "value %d is missing", v);
        }
    }

    // Run DFS from root to check subtree-difference constraints
    dfs(0, 0);

    // If we reach here, all checks passed
    ouf.quitf(_ok, "correct");
    return 0;
}
