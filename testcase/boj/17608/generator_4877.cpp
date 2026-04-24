#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small size for hand-checkable cases
    int N = rnd.next(2, 10);
    int shape = rnd.next(0, 4);
    vector<int> h(N);

    switch (shape) {
        case 0: {
            // Strictly increasing
            int startv = rnd.next(1, 10);
            int cur = startv;
            for (int i = 0; i < N; ++i) {
                h[i] = cur;
                cur += rnd.next(1, 10);
            }
            break;
        }
        case 1: {
            // Strictly decreasing
            int startv = rnd.next(N * 10, N * 20);
            int cur = startv;
            for (int i = 0; i < N; ++i) {
                h[i] = cur;
                cur -= rnd.next(1, 10);
            }
            break;
        }
        case 2: {
            // Fully random
            for (int i = 0; i < N; ++i)
                h[i] = rnd.next(1, 100);
            break;
        }
        case 3: {
            // Random with plateaus
            for (int i = 0; i < N; ++i)
                h[i] = rnd.next(1, 100);
            int K = rnd.next(1, N / 2);
            for (int k = 0; k < K; ++k) {
                int p = rnd.next(1, N - 1);
                h[p] = h[p - 1];
            }
            break;
        }
        case 4: {
            // Alternating peaks and valleys
            for (int i = 0; i < N; ++i) {
                if (i % 2 == 0)
                    h[i] = rnd.next(50, 100);
                else
                    h[i] = rnd.next(1, 49);
            }
            break;
        }
    }

    // Output in the required format
    println(N);
    for (int x : h)
        println(x);

    return 0;
}
