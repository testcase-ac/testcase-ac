#include "testlib.h"

#include <array>
#include <bitset>

using namespace std;

constexpr int MAX_N = 200'000;

array<int, MAX_N> ans_c, out_c, out_c_diff, out_p;
bitset<MAX_N> out_vis;
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    for (int i = 0; i < n-1; i++) {
        ans_c[i] = inf.readInt();
    }

    for (int i = 0; i < n; i++) {
        int v = ouf.readInt(1, n, format("p_%d", i+1));
        quitif(out_vis.test(v-1), _wa, "vertex %d was used more than once", v);
        out_vis.set(v-1);
        out_p[i] = v;
    }

    quitif(out_p[0] != 1, _wa, "path does not start at 1: p_1 != 1");
    quitif(out_p[n-1] != n, _wa, "path does not end at N: p_%d != %d", n, n);

    int cur = 1;
    for (int i = 1; i < n; i++) {
        int next = out_p[i];

        int l = min(cur-1, next-1), r = max(cur-1, next-1);
        out_c_diff[l] += 1; out_c_diff[r] -= 1;

        cur = next;
    }
    
    out_c[0] = out_c_diff[0];
    for (int i = 1; i < n-1; i++) {
        out_c[i] = out_c[i-1] + out_c_diff[i];
    }
    
    for (int i = 0; i < n-1; i++) {
        quitif(ans_c[i] != out_c[i], _wa, "edge count mismatch: expected c_%d = %d, found %d", i+1, ans_c[i], out_c[i]);
    }

    quitf(_ok, "mazassumnida!!");
    return 0;
}
