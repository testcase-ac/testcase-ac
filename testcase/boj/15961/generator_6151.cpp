#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose belt size N between small and medium for readability
    int N = rnd.next(5, 15);
    // Window size k between 2 and min(N, 7)
    int k = rnd.next(2, min(N, 7));
    // Number of sushi types d at least k+1 up to around 10
    int d_min = k + 1;
    int d_max = max(d_min, 10);
    int d = rnd.next(d_min, d_max);
    // Coupon sushi type
    int c = rnd.next(1, d);

    // Generate initial belt with random types
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        a[i] = rnd.next(1, d);
    }

    // With 50% chance, ensure coupon type is absent in the belt
    bool forceAbsent = rnd.next(0, 1) == 1;
    if (forceAbsent) {
        for (int i = 0; i < N; i++) {
            if (a[i] == c) {
                // replace with some other type
                int x;
                do { x = rnd.next(1, d); } while (x == c);
                a[i] = x;
            }
        }
    } else {
        // ensure at least one c in the belt
        bool found = false;
        for (int x : a) if (x == c) { found = true; break; }
        if (!found) {
            int pos = rnd.next(0, N-1);
            a[pos] = c;
        }
    }

    // Introduce some clusters of repeated types to catch sliding-window bugs
    int clusters = rnd.next(1, 3);
    for (int i = 0; i < clusters; i++) {
        int t = rnd.next(1, d);
        int len = rnd.next(2, min(N, 5));
        int start = rnd.next(0, N-1);
        for (int j = 0; j < len; j++) {
            a[(start + j) % N] = t;
        }
    }

    // Output
    println(N, d, k, c);
    for (int x : a) {
        println(x);
    }
    return 0;
}
