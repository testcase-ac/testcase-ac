#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N with variability: edge, small, medium
    int N;
    double nmode = rnd.next();
    if (nmode < 0.1) {
        N = 1;
    } else if (nmode < 0.3) {
        N = rnd.next(2, 5);
    } else if (nmode < 0.6) {
        N = rnd.next(6, 15);
    } else {
        N = rnd.next(16, 30);
    }
    // Generate first permutation a
    vector<int> a(N), b(N);
    iota(a.begin(), a.end(), 1);
    shuffle(a.begin(), a.end());
    // Copy to b and apply a few modes (guard single-swap to avoid N=1 infinite loop)
    b = a;
    if (N >= 2) {
        double bmode = rnd.next();
        if (bmode < 0.1) {
            // identical to a
        } else if (bmode < 0.2) {
            // reversed
            reverse(b.begin(), b.end());
        } else if (bmode < 0.3) {
            // single swap
            int i = rnd.next(0, N-1), j = rnd.next(0, N-1);
            while (j == i) j = rnd.next(0, N-1);
            swap(b[i], b[j]);
        } else if (bmode < 0.6) {
            // fully random
            shuffle(b.begin(), b.end());
        } else {
            // near-identity: a few random swaps
            int swaps = rnd.next(1, max(1, N/5));
            for (int k = 0; k < swaps; k++) {
                int i = rnd.next(0, N-1), j = rnd.next(0, N-1);
                if (i != j) swap(b[i], b[j]);
            }
        }
    }
    // Generate prices with varied distributions
    vector<int> p(N);
    double pmode = rnd.next();
    if (pmode < 0.2) {
        // fully random in [1,1000]
        for (int i = 0; i < N; i++) p[i] = rnd.next(1, 1000);
    } else if (pmode < 0.4) {
        // small prices
        for (int i = 0; i < N; i++) p[i] = rnd.next(1, 10);
    } else if (pmode < 0.6) {
        // large prices
        for (int i = 0; i < N; i++) p[i] = rnd.next(990, 1000);
    } else if (pmode < 0.7) {
        // constant price
        int c = rnd.next(1, 1000);
        for (int i = 0; i < N; i++) p[i] = c;
    } else if (pmode < 0.85) {
        // increasing sequence up to 1000
        for (int i = 0; i < N; i++) {
            int step = max(1, N-1);
            p[i] = min(1 + i * (1000 / step), 1000);
        }
    } else {
        // clustered low and high then shuffle
        vector<int> tmp;
        for (int i = 0; i < N/2; i++) tmp.push_back(rnd.next(1, 10));
        for (int i = N/2; i < N; i++) tmp.push_back(rnd.next(990, 1000));
        shuffle(tmp.begin(), tmp.end());
        p = tmp;
    }
    // Output the test case
    println(N);
    for (int i = 0; i < N; i++) {
        println(a[i], b[i], p[i]);
    }
    return 0;
}
