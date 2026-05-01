#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Pick N between 1 and 20 for hand-checkable size, sometimes only one banana
    int N = rnd.next(1, 20);
    // K may be up to N+5 to include the case K > N
    int K = rnd.next(1, N + 5);
    // C relative small constant cost
    int C = rnd.next(1, 50);

    // Generate banana weights with diverse patterns
    vector<int> a(N);
    int pattern = rnd.next(0, 3);
    if (pattern == 0) {
        // Completely random weights
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(1, 20);
        }
    } else if (pattern == 1) {
        // Strictly increasing sequence
        int base = rnd.next(1, 5);
        int delta = rnd.next(1, 5);
        for (int i = 0; i < N; i++) {
            a[i] = base + delta * i;
        }
    } else if (pattern == 2) {
        // Strictly decreasing sequence
        int base = rnd.next(100, 200);
        int delta = rnd.next(1, 5);
        for (int i = 0; i < N; i++) {
            a[i] = max(1, base - delta * i);
        }
    } else {
        // Clustered small and large weights
        for (int i = 0; i < N; i++) {
            if (rnd.next() < 0.5)
                a[i] = rnd.next(1, 5);
            else
                a[i] = rnd.next(10, 20);
        }
    }

    // Output in the required format
    println(N);
    println(K, C);
    println(a);

    return 0;
}
