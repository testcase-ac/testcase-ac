#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = rnd.next(2, 16);
    int pattern = rnd.next(0, 5);
    vector<int> A(N);

    switch (pattern) {
        case 0: { // strictly descending
            A[0] = rnd.next(500000, 1000000);
            for (int i = 1; i < N; i++) {
                A[i] = rnd.next(1, A[i - 1]);
            }
            break;
        }
        case 1: { // fully random
            for (int i = 0; i < N; i++)
                A[i] = rnd.next(1, 1000000);
            break;
        }
        case 2: { // clustered values
            int k = rnd.next(1, min(5, N));
            vector<int> bases(k);
            for (int i = 0; i < k; i++)
                bases[i] = rnd.next(1, 1000000);
            shuffle(bases.begin(), bases.end());
            for (int i = 0; i < N; i++)
                A[i] = rnd.any(bases);
            break;
        }
        case 3: { // zigzag low/high
            int low = rnd.next(1, 500000);
            int high = rnd.next(low, 1000000);
            for (int i = 0; i < N; i++)
                A[i] = (i % 2 == 0 ? low : high);
            break;
        }
        case 4: { // non-decreasing
            A[0] = rnd.next(1, 1000000);
            for (int i = 1; i < N; i++) {
                int add = rnd.next(0, 500000);
                long long val = (long long)A[i - 1] + add;
                A[i] = (int)min(val, 1000000LL);
            }
            break;
        }
        case 5: { // sorted then small reversed segment
            A[0] = rnd.next(1, 1000000);
            for (int i = 1; i < N; i++) {
                int add = rnd.next(0, 500000);
                long long val = (long long)A[i - 1] + add;
                A[i] = (int)min(val, 1000000LL);
            }
            if (N >= 2) {
                int len = rnd.next(2, min(N, 4));
                int start = rnd.next(0, N - len);
                reverse(A.begin() + start, A.begin() + start + len);
            }
            break;
        }
    }

    // occasional single adjacent swap
    if (N >= 2 && rnd.next(0, 1)) {
        int i = rnd.next(0, N - 2);
        swap(A[i], A[i + 1]);
    }

    println(N);
    println(A);
    return 0;
}
