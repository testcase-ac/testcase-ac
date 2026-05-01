#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N size
    int t = rnd.next(1, 4);
    int N;
    if (t == 1) N = rnd.next(1, 3);
    else if (t == 2) N = rnd.next(4, 10);
    else if (t == 3) N = rnd.next(11, 20);
    else N = rnd.next(21, 30);

    // Value range C
    int C;
    if (N == 1) {
        C = 1;
    } else {
        C = rnd.next(2, min(N, 20));
    }

    // Choose pattern type: 1=random, 2=palindrome (odd N), 3=alternating
    vector<int> patterns;
    patterns.push_back(1);
    if (N >= 3 && N % 2 == 1) patterns.push_back(2);
    if (C >= 2) patterns.push_back(3);
    int pat = rnd.any(patterns);

    vector<int> a;
    if (pat == 1) {
        // Pure random with no equal adjacent
        for (int i = 0; i < N; ++i) {
            int v = rnd.next(1, C);
            if (i > 0) {
                while (v == a.back()) v = rnd.next(1, C);
            }
            a.push_back(v);
        }
    } else if (pat == 3) {
        // Alternating between two values
        int v1 = rnd.next(1, C);
        int v2 = rnd.next(1, C);
        while (v2 == v1) v2 = rnd.next(1, C);
        for (int i = 0; i < N; ++i) {
            a.push_back((i % 2 == 0) ? v1 : v2);
        }
    } else {
        // Palindrome for odd N
        int firstHalfSize = (N + 1) / 2;
        vector<int> first;
        for (int i = 0; i < firstHalfSize; ++i) {
            int v = rnd.next(1, C);
            if (i > 0) {
                while (v == first.back()) v = rnd.next(1, C);
            }
            first.push_back(v);
        }
        // Build full palindrome
        a = first;
        int mirroredLen = N - firstHalfSize;
        for (int i = 0; i < mirroredLen; ++i) {
            // Mirror skipping the center
            a.push_back(first[firstHalfSize - 2 - i]);
        }
    }

    // Output
    println(N);
    println(a);

    return 0;
}
