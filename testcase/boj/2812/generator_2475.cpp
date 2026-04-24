/* generator code */
#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small size N between 2 and 10
    int N = rnd.next(2, 10);

    // Choose K biased low, high, or uniform
    int K;
    double p = rnd.next();
    if (p < 0.33) {
        // bias low: minimum of 2 samples from [0, N-2], +1 -> [1, N-1]
        K = rnd.wnext(N-1, -2) + 1;
    } else if (p < 0.66) {
        // bias high: maximum of 2 samples from [0, N-2], +1 -> [1, N-1]
        K = rnd.wnext(N-1, 2) + 1;
    } else {
        // uniform from 1 to N-1
        K = rnd.next(1, N-1);
    }

    // Build the N-digit number string according to a random pattern
    string pattern = rnd.next("rand|asc|desc|blocks");
    vector<int> digits(N, 0);

    if (pattern == "rand") {
        // Fully random, first digit non-zero
        digits[0] = rnd.next(1, 9);
        for (int i = 1; i < N; i++) {
            digits[i] = rnd.next(0, 9);
        }
    }
    else if (pattern == "asc") {
        // Non-decreasing sequence
        int cur = rnd.next(1, 9);
        digits[0] = cur;
        for (int i = 1; i < N; i++) {
            // can stay or increase up to 9
            int maxDelta = 9 - cur;
            int delta = rnd.next(0, maxDelta);
            cur += delta;
            digits[i] = cur;
        }
    }
    else if (pattern == "desc") {
        // Non-increasing sequence
        int cur = rnd.next(1, 9);
        digits[0] = cur;
        for (int i = 1; i < N; i++) {
            // can stay or decrease down to 0
            int maxDelta = cur;
            int delta = rnd.next(0, maxDelta);
            cur -= delta;
            digits[i] = cur;
        }
    }
    else { // blocks
        // Consecutive blocks of equal digits
        int i = 0;
        while (i < N) {
            int len = rnd.next(1, N - i);
            int d = rnd.next(0, 9);
            if (i == 0 && d == 0) {
                d = rnd.next(1, 9);
            }
            for (int j = 0; j < len; j++) {
                digits[i + j] = d;
            }
            i += len;
        }
    }

    // Convert digits to string
    string s;
    s.reserve(N);
    for (int d : digits) s.push_back(char('0' + d));

    // Output
    println(N, K);
    println(s);

    return 0;
}
