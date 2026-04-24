#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose minY and maxY
    int minY = rnd.next(-10, 0);
    int maxY = rnd.next(minY + 1, 10);

    // Number of segments
    int n = rnd.next(1, 10);

    // Range for x-coordinates
    int R = rnd.next(10, 50);
    vector<int> xs;
    for (int x = -R; x <= R; ++x) {
        xs.push_back(x);
    }
    shuffle(xs.begin(), xs.end());
    xs.resize(2 * n);

    vector<pair<int,int>> segs;
    for (int i = 0; i < n; ++i) {
        int ux = xs[i];
        int lx = xs[i + n];
        segs.emplace_back(ux, lx);
    }

    // Number of queries
    int m = rnd.next(1, 10);

    // Prepare queries as strings
    vector<string> qs;
    int pow10[4] = {1, 1, 10, 100};
    pow10[1] = 10; pow10[2] = 100; pow10[3] = 1000;
    for (int i = 0; i < m; ++i) {
        int d = rnd.next(1, 3); // decimal digits
        int d10 = pow10[d];
        // A in (minY*10^d, maxY*10^d)
        int loA = minY * d10;
        int hiA = maxY * d10;
        int A = rnd.next(loA + 1, hiA - 1);
        bool neg = A < 0;
        int B = neg ? -A : A;
        int ip = B / d10;
        int frac = B % d10;
        char buf[50];
        if (neg) {
            // negative
            snprintf(buf, sizeof(buf), "-%d.%0*d", ip, d, frac);
        } else {
            snprintf(buf, sizeof(buf), "%d.%0*d", ip, d, frac);
        }
        qs.emplace_back(buf);
    }

    // Output
    // First line: maxY minY
    println(maxY, minY);
    // segments
    println(n);
    for (auto &p : segs) {
        println(p.first, p.second);
    }
    // queries
    println(m);
    for (auto &s : qs) {
        println(s);
    }

    return 0;
}
