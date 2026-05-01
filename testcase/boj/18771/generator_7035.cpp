#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 7);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int n;
        if (rnd.next() < 0.7) n = rnd.next(2, 15);
        else n = rnd.next(16, 500);
        println(n);

        vector<int> f(n);
        double pw = rnd.next(0.0, 1.0);
        if (pw < 0.2) {
            // all positive small
            for (int i = 0; i < n; ++i)
                f[i] = rnd.next(1, 100);
        } else if (pw < 0.4) {
            // all negative small
            for (int i = 0; i < n; ++i)
                f[i] = -rnd.next(1, 100);
        } else {
            // mixed with large range
            for (int i = 0; i < n; ++i) {
                int v = rnd.next(1, 1000000);
                f[i] = rnd.next(0, 1) ? v : -v;
            }
        }
        println(f);

        int xi_max = min(n - 1, 300);
        vector< set<int> > deps(n);
        // random dependencies
        for (int i = 0; i < n; ++i) {
            int t = rnd.next(-3, 3);
            int xi = rnd.wnext(xi_max + 1, t);
            xi = min(xi, xi_max);
            while ((int)deps[i].size() < xi) {
                int j = rnd.next(0, n - 1);
                if (j != i) deps[i].insert(j);
            }
        }
        // add a hub dependency
        if (n > 2 && rnd.next() < 0.3) {
            int hub = rnd.next(0, n - 1);
            for (int i = 0; i < n; ++i) {
                if (i != hub && rnd.next() < 0.5 && (int)deps[i].size() < xi_max) {
                    deps[i].insert(hub);
                }
            }
        }
        // add some 2-cycles
        if (rnd.next() < 0.3) {
            int ccount = rnd.next(1, max(1, n / 4));
            for (int k = 0; k < ccount; ++k) {
                int u = rnd.next(0, n - 1), v = rnd.next(0, n - 1);
                if (u == v) continue;
                if ((int)deps[u].size() < xi_max && (int)deps[v].size() < xi_max
                    && !deps[u].count(v) && !deps[v].count(u)) {
                    deps[u].insert(v);
                    deps[v].insert(u);
                }
            }
        }
        // add a longer cycle
        if (n >= 3 && rnd.next() < 0.3) {
            int k = rnd.next(3, min(n, 10));
            vector<int> perm(n);
            iota(perm.begin(), perm.end(), 0);
            shuffle(perm.begin(), perm.end());
            perm.resize(k);
            for (int i = 0; i < k; ++i) {
                int u = perm[i], v = perm[(i + 1) % k];
                if ((int)deps[u].size() < xi_max) deps[u].insert(v);
            }
        }
        // output dependencies
        for (int i = 0; i < n; ++i) {
            vector<int> out;
            out.push_back((int)deps[i].size());
            for (int j : deps[i]) out.push_back(j + 1);
            println(out);
        }
    }
    return 0;
}
