#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checkability
    int n = rnd.next(1, 15);
    int t = rnd.next(1, 10);

    // Hyper-parameter: maximum array value
    int Amax = rnd.next(2, 10);
    // Hyper-parameter: distribution mode for a_i
    // 0 = uniform, 1 = bias small, 2 = bias large
    int mode = rnd.next(0, 2);

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (mode == 0) {
            a[i] = rnd.next(1, Amax);
        } else if (mode == 1) {
            // bias towards small values
            a[i] = rnd.wnext(Amax, -1) + 1;
        } else {
            // bias towards large values
            a[i] = rnd.wnext(Amax, +1) + 1;
        }
    }

    // Hyper-parameter: probability of full-range queries
    double pFull = rnd.next(0.0, 1.0);
    vector<pair<int,int>> queries;
    for (int i = 0; i < t; i++) {
        int l, r;
        if (rnd.next() < pFull) {
            l = 1;
            r = n;
        } else {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        }
        queries.emplace_back(l, r);
    }

    // Optionally shuffle query order
    shuffle(queries.begin(), queries.end());

    // Output
    println(n, t);
    println(a);
    for (auto &q : queries) {
        println(q.first, q.second);
    }

    return 0;
}
