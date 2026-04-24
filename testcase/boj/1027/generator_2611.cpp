/* generator code */
#include "testlib.h"
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of buildings
    int N = rnd.next(1, 10);
    println(N);

    // Generate diverse heights using wnext for extremes and averages
    vector<long long> h(N);
    for (int i = 0; i < N; i++) {
        int mag = rnd.next(1, 3);
        int t = rnd.next(0, 1) ? mag : -mag;
        // rnd.wnext(100, t) gives a 0..99 biased sample; +1 for 1..100
        h[i] = rnd.wnext(100, t) + 1;
    }

    // Output heights
    for (int i = 0; i < N; i++) {
        printf("%lld%c", h[i], (i + 1 == N ? '\n' : ' '));
    }

    return 0;
}
