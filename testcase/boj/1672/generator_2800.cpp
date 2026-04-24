#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Length of the DNA sequence
    int N = rnd.next(1, 20);

    // Decide a pattern type by a random probability
    double pat = rnd.next();

    string letters = "ACGT";
    string s(N, 'A');

    if (pat < 0.15) {
        // All same character
        char c = rnd.any(letters);
        for (int i = 0; i < N; i++) s[i] = c;
    }
    else if (pat < 0.30) {
        // Two-character alternating
        char c1 = rnd.any(letters);
        char c2;
        do { c2 = rnd.any(letters); } while (c2 == c1);
        for (int i = 0; i < N; i++) {
            s[i] = (i % 2 == 0 ? c1 : c2);
        }
    }
    else if (pat < 0.50) {
        // Block pattern: repeat a character in blocks of size b
        int b = rnd.next(1, N);
        char curr = rnd.any(letters);
        for (int i = 0; i < N; i++) {
            if (i % b == 0) curr = rnd.any(letters);
            s[i] = curr;
        }
    }
    else if (pat < 0.70) {
        // Palindromic structure
        int half = (N + 1) / 2;
        for (int i = 0; i < half; i++)
            s[i] = rnd.any(letters);
        for (int i = 0; i < N - half; i++)
            s[N - 1 - i] = s[i];
    }
    else if (pat < 0.90) {
        // Periodic pattern with small period
        int p = rnd.next(1, min(4, N));
        string pattern;
        for (int i = 0; i < p; i++)
            pattern += rnd.any(letters);
        for (int i = 0; i < N; i++)
            s[i] = pattern[i % p];
    }
    else {
        // Fully random
        for (int i = 0; i < N; i++)
            s[i] = rnd.any(letters);
    }

    // Output
    println(N);
    println(s);

    return 0;
}
