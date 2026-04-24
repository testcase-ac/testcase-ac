#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool is_bad_order(const vector<int>& a, int l, const vector<int>& perm) {
    int n = (int)a.size() - 1;
    vector<int> pos(n+1);
    for (int i = 1; i <= n; i++) pos[perm[i]] = i;
    for (int i = 1; i <= n; i++) {
        vector<int> neigh;
        for (int j = 1; j <= n; j++) {
            if (abs(a[i] - a[j]) <= l) neigh.push_back(j);
        }
        int sz = (int)neigh.size();
        int mn = n+1, mx = 0;
        for (int v : neigh) {
            mn = min(mn, pos[v]);
            mx = max(mx, pos[v]);
        }
        if (mx - mn + 1 != sz) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // small n, length l
        int n = rnd.next(2, 10);
        int l = rnd.next(1, 20);

        // generate endpoints sorted
        vector<int> a(n+1);
        int gapMax = rnd.next(0, 5);
        a[1] = rnd.next(-10, 10);
        for (int i = 2; i <= n; i++) {
            a[i] = a[i-1] + rnd.next(0, gapMax);
        }

        // decide if we want a bad ordering
        bool want_bad = rnd.next(0,1) == 1;
        // if we want bad but graph has no edges, force some overlap
        if (want_bad) {
            bool has_edge = false;
            for (int i = 1; i <= n && !has_edge; i++) {
                for (int j = i+1; j <= n; j++) {
                    if (abs(a[i] - a[j]) <= l) {
                        has_edge = true;
                        break;
                    }
                }
            }
            if (!has_edge) {
                // force one edge by shrinking gap
                a[2] = a[1] + rnd.next(0, l);
                for (int i = 3; i <= n; i++) {
                    a[i] = a[i-1] + rnd.next(0, gapMax);
                }
            }
        }

        // output header
        println(n, l);
        // endpoints
        for (int i = 1; i <= n; i++) {
            println(a[i]);
        }

        // generate ordering
        vector<int> perm(n+1), base(n);
        for (int i = 1; i <= n; i++) perm[i] = i;
        for (int i = 0; i < n; i++) base[i] = i+1;

        if (!want_bad) {
            // good: canonical
            for (int i = 1; i <= n; i++) {
                println(i);
            }
        } else {
            // bad: find a shuffle that violates consecutiveness
            vector<int> tmp = base;
            bool found = false;
            for (int it = 0; it < 1000 && !found; it++) {
                shuffle(tmp.begin(), tmp.end());
                for (int i = 1; i <= n; i++) perm[i] = tmp[i-1];
                if (is_bad_order(a, l, perm)) {
                    found = true;
                }
            }
            // as fallback, do one random shuffle
            if (!found) {
                shuffle(tmp.begin(), tmp.end());
                for (int i = 1; i <= n; i++) perm[i] = tmp[i-1];
            }
            for (int i = 1; i <= n; i++) {
                println(perm[i]);
            }
        }
    }
    return 0;
}
