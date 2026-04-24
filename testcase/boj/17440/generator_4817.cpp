#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of tournaments
    int N = rnd.next(1, 10);
    println(N);

    // Maximum rating value for small, hand-checkable tests
    const int Amax = 20;

    for (int i = 0; i < N; i++) {
        double p = rnd.next(0.0, 1.0);
        int A, B;

        if (p < 0.2) {
            // Singleton interval [A, A]
            A = rnd.next(1, Amax);
            B = A;
        } else if (p < 0.6) {
            // Small interval of length up to 3
            int maxLen = min(3, Amax - 1);
            int len = rnd.next(1, maxLen);
            A = rnd.next(1, Amax - len);
            B = A + len;
        } else {
            // Larger interval (length >= 4)
            int minLen = 4;
            int maxLen = Amax - 1;
            int len = rnd.next(minLen, maxLen);
            A = rnd.next(1, Amax - len);
            B = A + len;
        }

        println(A, B);
    }

    return 0;
}
