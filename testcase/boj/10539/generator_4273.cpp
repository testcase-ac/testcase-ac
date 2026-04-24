#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters
    int N = rnd.next(1, 10);
    vector<int> choices = {5, 10, 20};
    int B1max = rnd.any(choices);
    int B1 = rnd.next(1, B1max);
    int maxDelta = rnd.next(0, B1max);
    int tendency = rnd.next(0, 2); // 0: random, 1: non-decreasing, 2: non-increasing

    vector<long long> B(N);
    B[0] = B1;
    for (int i = 2; i <= N; i++) {
        long long prev = B[i-2];
        // lo = ceil(((i-1)*prev + 1) / i)
        long long lo = ((i-1) * prev + i) / i;
        if (lo < 1) lo = 1;
        long long bi;
        if (tendency == 0) {
            long long hi = lo + maxDelta;
            bi = rnd.next(lo, hi);
        } else if (tendency == 1) {
            long long newLo = prev > lo ? prev : lo;
            long long hi = newLo + maxDelta;
            bi = rnd.next(newLo, hi);
        } else {
            long long hi = lo + maxDelta;
            if (hi > prev) hi = prev;
            if (hi < lo) hi = lo;
            bi = rnd.next(lo, hi);
        }
        B[i-1] = bi;
    }

    // Output
    println(N);
    println(B);

    return 0;
}
