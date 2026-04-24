#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small N
    int N = rnd.next(3, 10);
    vector<int> a(N);

    // Some structured cases for diversity
    double mode = rnd.next();
    if (mode < 0.2) {
        // Simple staircase: always move +1
        for (int i = 0; i < N - 1; i++) a[i] = 1;
        a[N - 1] = 0;
    } else {
        // Hyperparameters for random distribution of zeros, small and large jumps
        double pZero  = rnd.next(0.0, 0.5);
        double pLarge = rnd.next(0.0, 0.5);
        int smallMax = max(1, min(3, N - 1));
        for (int i = 0; i < N; i++) {
            double r = rnd.next();
            if (r < pZero) {
                a[i] = 0;
            } else if (rnd.next() < pLarge) {
                // potentially large jump
                a[i] = rnd.next(1, N);
            } else {
                // small jump
                a[i] = rnd.next(1, smallMax);
            }
        }
    }

    // Output
    println(N);
    println(a);

    return 0;
}
