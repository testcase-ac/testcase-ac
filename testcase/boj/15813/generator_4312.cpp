#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose name length between 1 and 10
    int N = rnd.next(1, 10);

    // Choose generation pattern for diversity
    // 0: fully random letters
    // 1: all same letter
    // 2: consecutive alphabet substring
    // 3: palindromic
    // 4: high-value letters only (N..Z)
    int pattern = rnd.next(0, 4);

    string s;
    s.reserve(N);

    if (pattern == 0) {
        // Fully random uppercase letters
        for (int i = 0; i < N; i++) {
            char c = 'A' + rnd.next(0, 25);
            s.push_back(c);
        }
    } else if (pattern == 1) {
        // All the same letter
        char c = 'A' + rnd.next(0, 25);
        s.assign(N, c);
    } else if (pattern == 2) {
        // Consecutive substring of the alphabet
        int maxStart = max(0, 26 - N);
        int start = rnd.next(0, maxStart);
        for (int i = 0; i < N; i++) {
            s.push_back(char('A' + start + i));
        }
    } else if (pattern == 3) {
        // Palindrome
        int half = N / 2;
        string halfs;
        halfs.reserve(half);
        // generate first half
        for (int i = 0; i < half; i++) {
            halfs.push_back(char('A' + rnd.next(0, 25)));
        }
        s += halfs;
        if (N % 2 == 1) {
            s.push_back(char('A' + rnd.next(0, 25)));
        }
        // mirror
        reverse(halfs.begin(), halfs.end());
        s += halfs;
    } else {
        // High-value letters only (N to Z)
        for (int i = 0; i < N; i++) {
            s.push_back(char('A' + rnd.next(13, 25))); // 'N'..'Z'
        }
    }

    // Output
    println(N);
    printf("%s\n", s.c_str());

    return 0;
}
