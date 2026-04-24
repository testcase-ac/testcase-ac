#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Sizes of P and Q
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 10);
    // y-coordinates hyper-parameter: sometimes small delta, sometimes large
    int c1 = rnd.next(-100, 100);
    bool smallDy = rnd.next(0, 1);
    int d;
    if (smallDy) {
        d = rnd.next(-5, 5);
    } else {
        d = rnd.next(-100, 100);
    }
    int c2 = c1 + d;
    // x-coordinate pool range: ensure enough elements for P and Q
    int minRange = n + m - 1;
    int range = rnd.next(minRange, 200);
    int Xmin = rnd.next(-100, 100);
    int Xmax = Xmin + range;
    // build pool of x-coordinates
    vector<int> pool;
    for (int x = Xmin; x <= Xmax; x++) {
        pool.push_back(x);
    }
    // shuffle pool
    shuffle(pool.begin(), pool.end());
    // pick P as first n
    vector<int> P(pool.begin(), pool.begin() + n);
    // hyper-parameter: decide overlap count k between P and Q
    bool overl = rnd.next(0, 1);
    int maxOverlap = min(n, m);
    int k = overl ? rnd.next(1, maxOverlap) : 0;
    // build Q
    vector<int> Q;
    // choose k points from P to be in Q
    if (k > 0) {
        vector<int> tmp = P;
        shuffle(tmp.begin(), tmp.end());
        for (int i = 0; i < k; i++) {
            Q.push_back(tmp[i]);
        }
    }
    // build availability for remaining Q points: all xs not in P
    vector<int> avail;
    for (int x : pool) {
        bool inP = false;
        for (int y : P) if (y == x) { inP = true; break; }
        if (!inP) avail.push_back(x);
    }
    shuffle(avail.begin(), avail.end());
    int rem = m - k;
    for (int i = 0; i < rem; i++) {
        Q.push_back(avail[i]);
    }
    // final shuffle of P and Q
    shuffle(P.begin(), P.end());
    shuffle(Q.begin(), Q.end());
    // output according to statement
    println(n, m);
    println(c1, c2);
    println(P);
    println(Q);
    return 0;
}
