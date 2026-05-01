#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of rooms on the circle
    int N = rnd.next(2, 12);
    vector<ll> C(N);

    // Diversify patterns via modes
    double mode = rnd.next(0.0, 1.0);
    if (mode < 0.15) {
        // All zeroes
        fill(C.begin(), C.end(), 0LL);
    } else if (mode < 0.30) {
        // All same small value
        ll v = rnd.next(1, 5);
        fill(C.begin(), C.end(), v);
    } else if (mode < 0.45) {
        // All same large value
        ll v = rnd.next(100000000000LL, 1000000000000LL);
        fill(C.begin(), C.end(), v);
    } else if (mode < 0.60) {
        // Alternating zero and small
        ll v = rnd.next(1, 20);
        for (int i = 0; i < N; i++)
            C[i] = (i % 2 == 0 ? v : 0LL);
    } else if (mode < 0.75) {
        // Alternating zero and large
        ll v = rnd.next(100000000000LL, 1000000000000LL);
        for (int i = 0; i < N; i++)
            C[i] = (i % 2 == 0 ? v : 0LL);
    } else {
        // Mixed random values: zeros, small, medium, large
        for (int i = 0; i < N; i++) {
            double p = rnd.next();
            if (p < 0.30) {
                C[i] = 0;
            } else if (p < 0.60) {
                C[i] = rnd.next(1, 100);
            } else if (p < 0.90) {
                C[i] = rnd.next(1000LL, 1000000LL);
            } else {
                C[i] = rnd.next(100000000000LL, 1000000000000LL);
            }
        }
    }

    // Occasionally shuffle to break positional patterns
    if (rnd.next() < 0.3)
        shuffle(C.begin(), C.end());

    // Output
    println(N);
    println(C);

    return 0;
}
