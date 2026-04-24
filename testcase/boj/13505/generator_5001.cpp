#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand-checking
    int N = rnd.next(2, 10);
    vector<int> a(N);

    // Choose a generation strategy for diversity
    int type = rnd.next(0, 4);
    switch (type) {
        case 0: {
            // Fully random values up to 1e9
            for (int i = 0; i < N; i++) {
                a[i] = rnd.next(0, 1000000000);
            }
            break;
        }
        case 1: {
            // High-bit-density numbers, but clamp to <=1e9
            for (int i = 0; i < N; i++) {
                long long x = 0;
                for (int b = 0; b < 30; b++) {
                    if (rnd.next() < 0.7 && x + (1LL << b) <= 1000000000)
                        x |= (1 << b);
                }
                a[i] = int(x);
            }
            break;
        }
        case 2: {
            // Powers of two (and zeros)
            for (int i = 0; i < N; i++) {
                if (rnd.next(0, 1) == 0) {
                    a[i] = 0;
                } else {
                    int p = rnd.next(0, 29);
                    a[i] = (1 << p);
                }
            }
            break;
        }
        case 3: {
            // Many duplicates from small base set
            int B = rnd.next(1, N);
            vector<int> bases(B);
            for (int i = 0; i < B; i++) {
                bases[i] = rnd.next(0, 1000);
            }
            for (int i = 0; i < N; i++) {
                a[i] = rnd.any(bases);
            }
            break;
        }
        case 4: {
            // Arithmetic progression
            int start = rnd.next(0, 100);
            int diff  = rnd.next(1, 10);
            for (int i = 0; i < N; i++) {
                a[i] = start + i * diff;
            }
            break;
        }
    }

    // Shuffle to remove any ordering bias
    shuffle(a.begin(), a.end());

    // Output format
    println(N);
    println(a);

    return 0;
}
