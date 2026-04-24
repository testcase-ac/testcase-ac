#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small sizes for hand-checking
    int N = rnd.next(1, 10);
    int K = rnd.next(1, N);

    // Generate temperatures with diverse patterns
    vector<int> a(N);
    int mode = rnd.next(0, 6);
    switch (mode) {
        case 0: {
            // Full uniform random
            for (int i = 0; i < N; i++)
                a[i] = rnd.next(0, 65535);
            break;
        }
        case 1: {
            // Narrow uniform random
            int low = rnd.next(0, 65000);
            int high = min(low + 1000, 65535);
            for (int i = 0; i < N; i++)
                a[i] = rnd.next(low, high);
            break;
        }
        case 2: {
            // Increasing noisy
            a[0] = rnd.next(0, 1000);
            for (int i = 1; i < N; i++) {
                a[i] = a[i-1] + rnd.next(0, 2000);
                if (a[i] > 65535) a[i] = 65535;
            }
            break;
        }
        case 3: {
            // Decreasing noisy
            a[0] = rnd.next(55535, 65535);
            for (int i = 1; i < N; i++) {
                a[i] = a[i-1] - rnd.next(0, 2000);
                if (a[i] < 0) a[i] = 0;
            }
            break;
        }
        case 4: {
            // Constant sequence
            int v = rnd.next(0, 65535);
            for (int i = 0; i < N; i++)
                a[i] = v;
            break;
        }
        case 5: {
            // Small values only
            for (int i = 0; i < N; i++)
                a[i] = rnd.next(0, 10);
            break;
        }
        case 6: {
            // Large values only
            int low = rnd.next(65000, 65535);
            for (int i = 0; i < N; i++)
                a[i] = rnd.next(low, 65535);
            break;
        }
    }

    // Output in required format
    println(N, K);
    for (int x : a)
        println(x);

    return 0;
}
