#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N so that there's room for 3 segments of length K
    int N = rnd.next(4, 10);
    int K_max = (N - 1) / 3;  // K < N/3
    int K = rnd.next(1, K_max);

    vector<int> a(N);
    // Hyper-parameter: pattern type
    int pattern = rnd.next(0, 3);
    if (pattern == 0) {
        // random values
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(0, 100);
        }
    } else if (pattern == 1) {
        // ascending
        for (int i = 0; i < N; i++) {
            a[i] = min(i * 10 + rnd.next(0, 9), 100);
        }
    } else if (pattern == 2) {
        // descending
        for (int i = 0; i < N; i++) {
            a[i] = min((N - 1 - i) * 10 + rnd.next(0, 9), 100);
        }
    } else {
        // peak and valley
        for (int i = 0; i < N; i++) {
            if (rnd.next(0, 1) == 0)
                a[i] = rnd.next(60, 100);
            else
                a[i] = rnd.next(0, 40);
        }
    }

    // Output in required format
    println(N);
    println(a);
    println(K);

    return 0;
}
