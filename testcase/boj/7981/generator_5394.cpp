#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of devices
    int n = rnd.next(1, 10);

    // Hyper-parameter: total restart events across all devices
    int totalR = rnd.next(n, min(20, n * 5));

    // Distribute at least one restart per device
    vector<int> r(n + 1, 1);
    int rem = totalR - n;
    for (int i = 1; i <= n && rem > 0; ++i) {
        int add = rnd.next(0, rem);
        r[i] += add;
        rem -= add;
    }
    if (rem > 0) {
        // dump leftovers on device 1
        r[1] += rem;
    }

    // Hyper-parameter: max extra cost for strong shock
    int z_delta_max = rnd.next(1, 15);

    // Generate u, z and restart lists
    vector<int> u(n + 1), z(n + 1);
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n; ++i) {
        u[i] = rnd.next(1, 10);
        z[i] = u[i] + rnd.next(1, z_delta_max);
        g[i].reserve(r[i]);
        for (int j = 0; j < r[i]; ++j) {
            // restart any device uniformly
            g[i].push_back(rnd.next(1, n));
        }
        // shuffle restart order for diversity
        shuffle(g[i].begin(), g[i].end());
    }

    // Output
    println(n);
    for (int i = 1; i <= n; ++i) {
        // print u_i, z_i, r_i and the g_i list
        printf("%d %d %d", u[i], z[i], r[i]);
        for (int x : g[i]) {
            printf(" %d", x);
        }
        printf("\n");
    }

    return 0;
}
