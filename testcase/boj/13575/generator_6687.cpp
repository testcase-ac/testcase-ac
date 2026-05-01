#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose a medium or small scenario
    int scenario = rnd.next(0, 4);
    int N, K;
    if (scenario == 0) {
        // medium size for stress
        N = rnd.next(10, 30);
        K = rnd.next(10, 30);
    } else {
        // small size for manual verification
        N = rnd.next(1, 7);
        K = rnd.next(1, 10);
    }
    // Possibly enforce a common GCD to catch gcd-related bugs
    bool forceGcd = rnd.next(0, 4) == 0;
    int g = 1;
    if (forceGcd) {
        g = rnd.next(2, 5);
    }
    // Possibly all values equal
    bool allEqual = rnd.next(0, 5) == 0;
    vector<int> a(N);
    if (allEqual) {
        int val = rnd.next(1, 100);
        val = val * g;
        for (int i = 0; i < N; i++) {
            a[i] = val;
        }
    } else {
        for (int i = 0; i < N; i++) {
            int v;
            if (forceGcd) {
                v = rnd.next(1, 20) * g;
            } else {
                v = rnd.next(1, 100);
            }
            a[i] = v;
        }
        // Introduce a duplicate with some probability
        if (N >= 2 && rnd.next(0, 3) == 0) {
            int i = rnd.next(0, N-1), j = rnd.next(0, N-1);
            a[j] = a[i];
        }
    }
    // Shuffle to avoid sorted order
    shuffle(a.begin(), a.end());
    // Output
    println(N, K);
    println(a);
    return 0;
}
