#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // sequence length N in [3,50]
    int N = rnd.next(3, 50);
    // decide arithmetic or geometric
    bool isArith = rnd.next(0, 1);

    vector<long long> a(N);
    if (isArith) {
        // arithmetic sequence: choose first term P
        bool largeP = rnd.next(0, 1);
        long long P = largeP ? rnd.next(500000LL, 1000000LL) : rnd.next(1LL, 1000LL);
        // compute allowable diff so terms stay in [1,1e6]
        long long maxPos = (1000000LL - P) / (N - 1);
        long long minNeg = -((P - 1) / (N - 1));
        // occasionally make it a constant sequence
        bool zeroDiff = rnd.next(0, 9) == 0;
        long long diff;
        if (zeroDiff || minNeg > maxPos) {
            diff = 0;
        } else {
            diff = rnd.next(minNeg, maxPos);
        }
        // build sequence
        for (int i = 0; i < N; i++) {
            a[i] = P + diff * i;
        }
    } else {
        // geometric sequence: choose first term P in small, medium, or large bucket
        int bucket = rnd.next(0, 2);
        long long P;
        if (bucket == 0) {
            P = rnd.next(1LL, 10LL);
        } else if (bucket == 1) {
            P = rnd.next(11LL, 1000LL);
        } else {
            P = rnd.next(1001LL, 1000000LL);
        }
        a[0] = P;
        // compute max integer ratio r so that terms <=1e6
        double limit = 1000000.0 / P;
        long long maxR = floor(pow(limit, 1.0 / (N - 1)) + 1e-9);
        if (maxR < 1) maxR = 1;
        // sometimes pick ratio = 1
        bool unitRatio = rnd.next(0, 9) == 0;
        long long r;
        if (unitRatio || maxR == 1) {
            r = 1;
        } else {
            // pick r in [2, maxR]
            r = rnd.next(2LL, maxR);
        }
        // build sequence
        for (int i = 1; i < N; i++) {
            a[i] = a[i - 1] * r;
        }
    }

    // output
    println(N);
    for (long long v : a) {
        println(v);
    }
    return 0;
}
