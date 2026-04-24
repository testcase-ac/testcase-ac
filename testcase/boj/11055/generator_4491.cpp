#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small size for hand-checking
    int N = rnd.next(1, 10);
    vector<int> A(N);

    // If only one element, just output a random value
    if (N == 1) {
        A[0] = rnd.next(1, 1000);
        println(N);
        println(A);
        return 0;
    }

    // Ensure maxVal >= N so that strictly increasing/decreasing patterns are valid
    int maxVal = rnd.next(N, 1000);

    // Choose a pattern for diversity
    // 0: fully random
    // 1: strictly increasing
    // 2: strictly decreasing
    // 3: bitonic (increase then decrease)
    // 4: valley  (decrease then increase)
    int pattern = rnd.next(0, 4);

    if (pattern == 0) {
        // Random values
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(1, maxVal);
        }
    }
    else if (pattern == 1) {
        // Strictly increasing
        // base in [1, maxVal-N+1]
        int base = rnd.next(1, maxVal - N + 1);
        for (int i = 0; i < N; i++) {
            A[i] = base + i;
        }
    }
    else if (pattern == 2) {
        // Strictly decreasing
        int base = rnd.next(1, maxVal - N + 1);
        for (int i = 0; i < N; i++) {
            A[i] = base + (N - 1 - i);
        }
    }
    else if (pattern == 3) {
        // Bitonic: first increase for m elements, then decrease
        int m = rnd.next(1, N);
        int decLen = N - m;
        int base = rnd.next(1, maxVal - N + 1);
        vector<int> inc(m), dec;
        for (int i = 0; i < m; i++) {
            inc[i] = base + i;
        }
        if (decLen > 0) {
            int peak = inc.back();
            if (peak > 1) {
                for (int i = 0; i < decLen; i++) {
                    dec.push_back(rnd.next(1, peak - 1));
                }
            } else {
                for (int i = 0; i < decLen; i++) {
                    dec.push_back(1);
                }
            }
            sort(dec.begin(), dec.end(), greater<int>());
        }
        A.clear();
        A.insert(A.end(), inc.begin(), inc.end());
        A.insert(A.end(), dec.begin(), dec.end());
    }
    else {
        // Valley: first decrease for v elements, then increase
        int v = rnd.next(1, N - 1);
        int decLen = v, incLen = N - v;
        vector<int> dec(decLen), inc(incLen);
        // Decreasing part
        for (int i = 0; i < decLen; i++) {
            dec[i] = rnd.next(1, maxVal);
        }
        sort(dec.begin(), dec.end(), greater<int>());
        int bottom = dec.back();
        // Increasing part
        for (int i = 0; i < incLen; i++) {
            inc[i] = rnd.next(bottom, maxVal);
        }
        sort(inc.begin(), inc.end());
        A.clear();
        A.insert(A.end(), dec.begin(), dec.end());
        A.insert(A.end(), inc.begin(), inc.end());
    }

    // Output the test case
    println(N);
    println(A);

    return 0;
}
