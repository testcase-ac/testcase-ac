#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of flowers
    int N = rnd.next(1, 10);
    // Choose a value range for petals
    double pr = rnd.next();
    int lo, hi;
    if (pr < 0.3) {
        lo = 1; hi = 10;
    } else if (pr < 0.6) {
        lo = 100; hi = 200;
    } else if (pr < 0.9) {
        lo = 800; hi = 1000;
    } else {
        lo = 1; hi = 1000;
    }
    // Sequence shape type: 0=uniform,1=asc,2=desc,3=mountain,4=valley,5=random,6=few distinct
    int type = rnd.next(0, 6);
    vector<int> p(N);
    switch (type) {
        case 0: { // uniform
            int x = rnd.next(lo, hi);
            for (int i = 0; i < N; i++) p[i] = x;
            break;
        }
        case 1: { // non-decreasing
            p[0] = rnd.next(lo, hi);
            for (int i = 1; i < N; i++) {
                int maxInc = hi - p[i-1];
                p[i] = p[i-1] + (maxInc > 0 ? rnd.next(0, maxInc) : 0);
            }
            break;
        }
        case 2: { // non-increasing
            p[0] = rnd.next(lo, hi);
            for (int i = 1; i < N; i++) {
                int maxDec = p[i-1] - lo;
                p[i] = p[i-1] - (maxDec > 0 ? rnd.next(0, maxDec) : 0);
            }
            break;
        }
        case 3: { // mountain
            int peak = rnd.next(0, N-1);
            p[0] = rnd.next(lo, hi);
            for (int i = 1; i <= peak; i++) {
                int maxInc = hi - p[i-1];
                p[i] = p[i-1] + (maxInc > 0 ? rnd.next(0, maxInc) : 0);
            }
            for (int i = peak+1; i < N; i++) {
                int maxDec = p[i-1] - lo;
                p[i] = p[i-1] - (maxDec > 0 ? rnd.next(0, maxDec) : 0);
            }
            break;
        }
        case 4: { // valley
            int trough = rnd.next(0, N-1);
            p[0] = rnd.next(lo, hi);
            for (int i = 1; i <= trough; i++) {
                int maxDec = p[i-1] - lo;
                p[i] = p[i-1] - (maxDec > 0 ? rnd.next(0, maxDec) : 0);
            }
            for (int i = trough+1; i < N; i++) {
                int maxInc = hi - p[i-1];
                p[i] = p[i-1] + (maxInc > 0 ? rnd.next(0, maxInc) : 0);
            }
            break;
        }
        case 5: { // fully random
            for (int i = 0; i < N; i++) p[i] = rnd.next(lo, hi);
            break;
        }
        case 6: { // few distinct values
            int D = rnd.next(1, min(N, 5));
            vector<int> vals;
            while ((int)vals.size() < D) {
                int v = rnd.next(lo, hi);
                bool ok = true;
                for (int x : vals) if (x == v) { ok = false; break; }
                if (ok) vals.push_back(v);
            }
            for (int i = 0; i < N; i++) {
                p[i] = rnd.any(vals);
            }
            break;
        }
    }
    // Output the test case
    println(N);
    println(p);
    return 0;
}
