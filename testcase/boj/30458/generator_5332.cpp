#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Basic parameters
    int minN = 3, maxN = 11;
    // Decide parity
    bool isOdd = rnd.next(0, 1) == 1;
    int N;
    do {
        N = rnd.next(minN, maxN);
    } while ((N % 2 == 1) != isOdd);

    // Decide yes/no case
    bool isYes = rnd.next(0, 1) == 1;

    string alph = "abcdefghijklmnopqrstuvwxyz";

    string S(N, '?');

    if (isYes) {
        // Build a palindrome directly
        int half = N / 2;
        // Choose a small set of letters for diversity
        int k = rnd.next(1, min(N, 5));
        string tmp = alph;
        shuffle(tmp.begin(), tmp.end());
        string letters = tmp.substr(0, k);

        // Generate half
        vector<char> halfv(half);
        for (int i = 0; i < half; i++) {
            halfv[i] = rnd.any(letters);
        }
        // Assign halves
        for (int i = 0; i < half; i++) {
            S[i] = halfv[i];
            S[N - 1 - i] = halfv[i];
        }
        if (isOdd) {
            char c = rnd.any(letters);
            S[half] = c;
        }
    } else {
        // Generate a no-case that violates the necessary condition
        if (!isOdd) {
            // Even N: ensure at least one character has odd total count
            // Pick c0 to appear exactly once
            char c0 = rnd.any(alph);
            // Build letters without c0
            string rest;
            for (char c : alph) if (c != c0) rest.push_back(c);
            // Place one c0 at random position
            int p0 = rnd.next(0, N - 1);
            S[p0] = c0;
            // Fill others with no c0
            for (int i = 0; i < N; i++) {
                if (i == p0) continue;
                S[i] = rnd.any(rest);
            }
        } else {
            // Odd N: ensure center character has even total count
            int half = N / 2;
            char c0 = rnd.any(alph);
            // letters without c0
            string rest;
            for (char c : alph) if (c != c0) rest.push_back(c);
            // Place c0 at center and one more elsewhere
            S[half] = c0;
            int p0;
            do {
                p0 = rnd.next(0, N - 1);
            } while (p0 == half);
            S[p0] = c0;
            // Fill other positions with no c0
            for (int i = 0; i < N; i++) {
                if (i == half || i == p0) continue;
                S[i] = rnd.any(rest);
            }
        }
    }

    // Output
    println(N);
    printf("%s\n", S.c_str());
    return 0;
}
