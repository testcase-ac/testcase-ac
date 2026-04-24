#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of haybales
    int N = rnd.next(2, 10);
    vector<int> F(N), S(N);

    // Hyper-parameter for flavor distribution
    int fmode = rnd.next(0, 1);
    for (int i = 0; i < N; i++) {
        if (fmode == 0) {
            // mostly small flavors
            F[i] = rnd.next(1, 5);
        } else {
            // wider range flavors
            F[i] = rnd.next(1, 20);
        }
    }

    // Hyper-parameter for spiciness distribution
    int smode = rnd.next(0, 1);
    for (int i = 0; i < N; i++) {
        if (smode == 0) {
            // mild overall
            S[i] = rnd.next(1, 10);
        } else {
            // can be quite spicy
            S[i] = rnd.next(1, 20);
        }
    }

    // Compute total flavor
    int totalFlavor = accumulate(F.begin(), F.end(), 0);

    // Choose M in diverse ways
    long long M;
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        // any requirement up to total flavor
        M = rnd.next(1, totalFlavor);
    } else if (mode == 1) {
        // base M on a random subarray sum
        int l = rnd.next(0, N-1);
        int r = rnd.next(l, N-1);
        int segSum = 0;
        for (int i = l; i <= r; i++) segSum += F[i];
        int lo = segSum - 2;
        if (lo < 1) lo = 1;
        M = rnd.next(lo, segSum);
    } else {
        // M close to total flavor
        int lo = totalFlavor > 5 ? totalFlavor - 5 : 1;
        M = rnd.next(lo, totalFlavor);
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(F[i], S[i]);
    }

    return 0;
}
