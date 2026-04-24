#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of groups
    int N = rnd.next(2, 10);

    // Choose a maximum snake count for diversity
    vector<int> Mopts = {5, 10, 20, 50, 100, 1000};
    int Mmax = rnd.any(Mopts);

    // Pattern selector
    int pattern = rnd.next(0, 4);
    int repv = 0;
    if (pattern == 4) repv = rnd.next(0, Mmax);

    // Generate groups
    vector<int> a(N);
    int spikePos = rnd.next(0, N - 1);
    for (int i = 0; i < N; i++) {
        switch (pattern) {
            case 0:
                // pure random
                a[i] = rnd.next(0, Mmax);
                break;
            case 1: {
                // roughly increasing
                int low = (int)((long long)Mmax * i / N);
                int high = (int)((long long)Mmax * (i + 1) / N);
                if (low > high) swap(low, high);
                a[i] = rnd.next(low, high);
                break;
            }
            case 2:
                // one spike
                if (i == spikePos) a[i] = Mmax;
                else a[i] = rnd.next(0, Mmax);
                break;
            case 3:
                // many zeros
                if (rnd.next() < 0.5) a[i] = 0;
                else a[i] = rnd.next(0, Mmax);
                break;
            case 4:
                // repeating value mixed with random
                if (rnd.next() < 0.5) a[i] = repv;
                else a[i] = rnd.next(0, Mmax);
                break;
        }
    }

    // Choose number of size changes K with bias
    int K;
    double p = rnd.next();
    if (p < 0.33)       K = rnd.wnext(N - 1, 2) + 1;
    else if (p < 0.66)  K = rnd.wnext(N - 1, -2) + 1;
    else                K = rnd.next(1, N - 1);

    // Output
    println(N, K);
    println(a);

    return 0;
}
