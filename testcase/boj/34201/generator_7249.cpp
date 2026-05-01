#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small or medium N
    int N = rnd.next(0, 1) == 0 ? rnd.next(1, 5) : rnd.next(6, 12);
    int mode = rnd.next(0, 3);
    vector<long long> A(N);
    long long s;

    if (mode == 0) {
        // All mirrors to the left of s
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(-30, 0);
        sort(A.begin(), A.end());
        s = A.back() + rnd.next(1, 10);
    } else if (mode == 1) {
        // All mirrors to the right of s
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(0, 30);
        sort(A.begin(), A.end());
        s = A.front() - rnd.next(1, 10);
    } else if (mode == 2) {
        // Uniform around s
        s = rnd.next(-10, 10);
        for (int i = 0; i < N; i++)
            A[i] = s + rnd.next(-15, 15);
        sort(A.begin(), A.end());
    } else {
        // Clustered around s with some duplicates
        s = rnd.next(-10, 10);
        int half = N / 2;
        for (int i = 0; i < half; i++)
            A[i] = s + rnd.next(-5, 5);
        for (int i = half; i < N; i++) {
            if (rnd.next(0, 1))
                A[i] = s + rnd.next(6, 15);
            else
                A[i] = s + rnd.next(-15, -6);
        }
        // Introduce some duplicates
        for (int i = 1; i < N; i++)
            if (rnd.next() < 0.3)
                A[i] = A[i - 1];
        sort(A.begin(), A.end());
    }

    // Output
    println(N, s);
    println(A);

    return 0;
}
