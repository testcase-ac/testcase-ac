#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N between 2 and 20, biased to smaller sizes
    int N = rnd.wnext(19, -1) + 2;
    vector<long long> A(N);

    // Choose a pattern for A to expose different behaviors
    int pat = rnd.next(0, 5);
    switch (pat) {
        case 0: {
            // Constant array
            long long base = rnd.next(1, 1000);
            for (int i = 0; i < N; i++) A[i] = base;
            break;
        }
        case 1: {
            // Strictly increasing
            A[0] = rnd.next(1, 50);
            for (int i = 1; i < N; i++) {
                A[i] = A[i-1] + rnd.next(1, 50);
            }
            break;
        }
        case 2: {
            // Strictly decreasing
            A[0] = rnd.next(1, 1000);
            for (int i = 1; i < N; i++) {
                A[i] = A[i-1] - rnd.next(1, 50);
                if (A[i] < 1) A[i] = 1;
            }
            break;
        }
        case 3: {
            // Small random fluctuations
            A[0] = rnd.next(1, 1000);
            for (int i = 1; i < N; i++) {
                A[i] = A[i-1] + rnd.next(-50, 50);
                if (A[i] < 1) A[i] = 1;
            }
            break;
        }
        case 4: {
            // Fully random in full range
            for (int i = 0; i < N; i++) {
                A[i] = rnd.next(1, 1000000);
            }
            break;
        }
        case 5: {
            // Clustered segments with occasional jumps
            int i = 0;
            while (i < N) {
                int len = rnd.next(1, min(5, N - i));
                long long base = rnd.next(1, 1000000);
                for (int j = i; j < i + len; j++) {
                    A[j] = base + rnd.next(-10, 10);
                    if (A[j] < 1) A[j] = 1;
                    if (A[j] > 1000000) A[j] = 1000000;
                }
                i += len;
            }
            break;
        }
    }

    // Output
    println(N);
    println(A);
    return 0;
}
